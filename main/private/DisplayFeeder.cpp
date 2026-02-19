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
    ESP_ERROR_CHECK(hd44780_switch_backlight(&lcd, true));
}

void DisplayFeeder::FetchNextAd() {
    if (deck) {
        currentCustomer = deck->Draw();
        currentAd = SelectAd();
        currentCustomer->AdsShown();
    }
}

void DisplayFeeder::ShowAd() {
    auto fixed = stringFixer->ToDisplay(currentAd.text);
    hd44780_gotoxy(&lcd, 0, 0);
    hd44780_puts(&lcd, fixed[0].c_str());
    hd44780_gotoxy(&lcd, 0, 1);
    hd44780_puts(&lcd, fixed[1].c_str());
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
