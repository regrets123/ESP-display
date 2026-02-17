idf_component_register(SRCS "main.cpp" "private/Customer.cpp" "private/Deck.cpp" "private/AdsTimer.cpp"
                    INCLUDE_DIRS "." "public" "private"
                    REQUIRES esp_timer)
