idf_component_register(SRCS "main.cpp" "private/Customer.cpp" "private/Deck.cpp" "private/AdsTimer.cpp"
                             "private/DisplayFeeder.cpp" "private/StringModifier.cpp"
                   INCLUDE_DIRS "." "public" "private"
                   REQUIRES esp_timer hd44780 pcf8574 i2cdev)
