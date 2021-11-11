#include "Freenove_WS2812_Lib_for_ESP32.h"

#define LED_PIN  18  // GPIO18 for ESP32-S2-Saola-1

// ESP32-S2-Saola-1 has only a single WS2812
#define CREATE_ESP32_WS2812_INSTANCE() Freenove_ESP32_WS2812 ws2812 = Freenove_ESP32_WS2812(1, LED_PIN, 0, TYPE_GRB)
#define ESP32_RED(val) ws2812.setLedColorData(0, val, 0, 0); ws2812.show()
#define ESP32_RED(r, g, b) ws2812.setLedColorData(0, r, g, b); ws2812.show()
#define ESP32_WS2812_SETUP(val) ws2812.begin(); ws2812.setBrightness(10); ESP32_RED(val)
