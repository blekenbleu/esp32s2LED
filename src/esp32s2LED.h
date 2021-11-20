// a wrapper for Freenove_WS2812_Lib_for_ESP32.h
#include "Freenove_WS2812_Lib_for_ESP32.h"

/* typical usage
 ; #include "esp32s2LED.h
 ;
 ; CREATE_ESP32_WS2812_INSTANCE();
 ;
 ; void setup() {
 ;   ...
 ;   ESP32_WS2812_SETUP(255);
 ;   ...
 ; }
 ;
 ; void loop() {
 ;   ESP32_RED(0);
 ;   ...
 ;   ...
 ;   ESP32_LED(0, 255, 0);  // green
 ; }
 */

#define WS2812_PIN  18  // GPIO18 for ESP32-S2-Saola-1M (WROOM)

// ESP32-S2-Saola-1M has only a single WS2812
#define CREATE_ESP32_WS2812_INSTANCE() Freenove_ESP32_WS2812 ws2812 \
        = Freenove_ESP32_WS2812(1, WS2812_PIN, 0, TYPE_GRB)

// only 255 brightness levels; setBrightness < 255 limits brightness and real granularity
#define ESP32_WS2812_SETUP(val) ({ \
        ws2812.begin(); \
        ws2812.setBrightness(255); \
        ESP32_RED(val); })

#define ESP32_RED(val) ws2812.setLedColor(0, val, 0, 0)

#define ESP32_LED(r, g, b) ws2812.setLedColor(0, r, g, b)
