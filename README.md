## esp32s2LED.h - a wrapper for [Freenove_WS2812_Lib_for_ESP32](../Freenove_WS2812_Lib_for_ESP32).h and (ESP32_S2_ISR_Servo)[https://github.com/khoih-prog/ESP32_S2_ISR_Servo]  
This library simplifies using an ESP32-S2 module with existing Arduino sketches that use an LED and/or hobby servos.  
Many ESP32 boards have a WS2812 instead of a simple LED, breaking many Arduino sketches.  
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
With this library, existing sketches with `#include "Servo.h"` should work as intended on ESP32-S2 boards.

