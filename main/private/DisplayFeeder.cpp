#include "DisplayFeeder.h"

#include <i2cdev.h>
#include <pcf8574.h>

#include "AdsTimer.h"
#include "StringModifier.h"

// File-scope statics — needed because write_cb is a plain C function pointer
// and cannot capture 'this'.
static i2c_dev_t s_pcf8574;

static esp_err_t write_lcd_data(const hd44780_t* lcd, uint8_t data) {
    return pcf8574_port_write(&s_pcf8574, data);
}

void DisplayFeeder::Init(Deck* deck, StringModifier* mod, AdsTimer* timer, Customer* cust) {
    this->deck = deck;
    this->stringFixer = mod;
    this->timer = timer;
    this->customer = cust;
    assert(this->deck);
    assert(this->stringFixer);
    assert(this->timer);
    assert(this->customer);

    // PCF8574 wiring to the HD44780 (bit positions on the expander):
    //   P0=RS  P1=RW  P2=E  P3=Backlight  P4=D4  P5=D5  P6=D6  P7=D7
    lcd.write_cb = write_lcd_data;
    lcd.font = HD44780_FONT_5X8;
    lcd.lines = LCD_ROWS;
    lcd.pins.rs = 0;
    lcd.pins.e = 2;
    lcd.pins.d4 = 4;
    lcd.pins.d5 = 5;
    lcd.pins.d6 = 6;
    lcd.pins.d7 = 7;
    lcd.pins.bl = 3;

    ESP_ERROR_CHECK(pcf8574_init_desc(&s_pcf8574, LCD_I2C_ADDR, I2C_NUM_0,
                                      (gpio_num_t)SDA, (gpio_num_t)SCL));
    ESP_ERROR_CHECK(hd44780_init(&lcd));

    static const uint8_t a_ring[8] = {
        0b00100,  // ..O..  circle
        0b00000,  //        gap
        0b01110,  // .OOO.  top of 'a'
        0b00001,  // ....O  right
        0b01111,  // .OOOO  middle
        0b10001,  // O...O  body
        0b01111,  // .OOOO  bottom
        0b00000,  //        empty (matching other chars)
    };
    ESP_ERROR_CHECK(hd44780_upload_character(&lcd, StringModifier::CGRAM_SLOT_A_RING, a_ring));

    ESP_ERROR_CHECK(hd44780_switch_backlight(&lcd, true));
}

void DisplayFeeder::FetchNextAd() {
    if (deck) {
        currentCustomer = deck->Draw();
        currentAd = SelectAd();
        currentCustomer->AdsShown();
        frameCount = 0;
        scrollOffset = 0;
        hd44780_control(&lcd, true, false, false);  // ensure display is on for new ad
    }
}

void DisplayFeeder::ShowAd() {
    frameCount++;
    switch (currentAd.adType) {
        case Customer::AdType::scroll: {
            ShowScroll();
            break;
        }
        case Customer::AdType::blink: {
            ShowBlink();
            break;
        }
        default: {
            ShowPlain();
            break;
        }
    }
}

void DisplayFeeder::ShowPlain() {
    auto fixed = stringFixer->ToDisplay(currentAd.text);
    hd44780_gotoxy(&lcd, 0, 0);
    hd44780_puts(&lcd, fixed[0].c_str());
    hd44780_gotoxy(&lcd, 0, 1);
    hd44780_puts(&lcd, fixed[1].c_str());
}

void DisplayFeeder::ShowScroll() {
    if (frameCount % 10 == 0)
        scrollOffset++;

    std::string name = currentCustomer->name;
    name.resize(16, ' ');

    std::string parsed = stringFixer->ParseSwedish(currentAd.text);
    std::string paddedText = std::string(16, ' ') + parsed + std::string(16, ' ');

    int maxOffset = (int)paddedText.size() - 16;
    if (scrollOffset >= maxOffset)
        scrollOffset = 0;

    std::string row1 = paddedText.substr(scrollOffset, 16);
    row1.resize(16, ' ');

    hd44780_gotoxy(&lcd, 0, 0);
    hd44780_puts(&lcd, name.c_str());
    hd44780_gotoxy(&lcd, 0, 1);
    hd44780_puts(&lcd, row1.c_str());
}

void DisplayFeeder::ShowBlink() {
    bool visible = (frameCount / 30) % 2 == 0;
    if (visible) {
        auto fixed = stringFixer->ToDisplay(currentAd.text);
        hd44780_gotoxy(&lcd, 0, 0);
        hd44780_puts(&lcd, fixed[0].c_str());
        hd44780_gotoxy(&lcd, 0, 1);
        hd44780_puts(&lcd, fixed[1].c_str());
    } else {
        hd44780_gotoxy(&lcd, 0, 0);
        hd44780_puts(&lcd, "                ");
        hd44780_gotoxy(&lcd, 0, 1);
        hd44780_puts(&lcd, "                ");
    }
}

Customer::Advertisement DisplayFeeder::SelectAd() {
    int indexToUse = -1;
    if (currentCustomer && currentCustomer == (customer->GetEdgeCaseCustomer())) {
        indexToUse = timer->IsEvenMinute();
    } else {
        indexToUse = currentCustomer->lastAdIndex;
    }
    return currentCustomer->ads[indexToUse];
}
