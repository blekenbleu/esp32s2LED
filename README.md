## esp32s2LED.h - a wrapper for [Freenove_WS2812_Lib_for_ESP32](../Freenove_WS2812_Lib_for_ESP32).h
A number of ESP32 modules have a WS2812 instead of an LED, breaking many Arduino sketches.  
`esp32s2LED.h` provides a relatively simple way to patch those sketches:
```
#include "esp32s2LED.h"
 
CREATE_ESP32_WS2812_INSTANCE();
 
void setup() {
  ...
  ESP32_WS2812_SETUP(255);   // initialize the WS2812 to red
  ...
}
 
void loop() {
  ESP32_RED(0);          // turn it off
  ...
  ...
  ESP32_LED(0, 255, 0);  // green
}
```

