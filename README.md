## esp32s2LED.h - a wrapper for Freenove_WS2812_Lib_for_ESP32.h
A number of ESP32 modules have a WS2812 instead of an LED,  
which breaks many Arduino sketches.  
`esp32s2LED.h` provides a relatively painless way to patch those sketches:
```
#include "esp32s2LED.h
 
CREATE_ESP32_WS2812_INSTANCE();
 
void setup() {
  ...
  ESP32_WS2812_SETUP(255);
  ...
}
 
void loop() {
  ESP32_RED(0);
  ...
  ...
  ESP32_LED(0, 255, 0);  // green
}
```

