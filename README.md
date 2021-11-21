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
See also [Arduino and ESP32-S2-Saola-1](https://blekenbleu.github.io/ESP32)
and its [libraries descriptions](https://blekenbleu.github.io/ESP32/libraries)  

[Freenove_WS2812_Lib_for_ESP32](https://www.arduino.cc/reference/en/libraries/freenove-ws2812-lib-for-esp32/) uses
[`rmt_data_t` in `esp32-hal-rmt.h`](https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/esp32-hal-rmt.h) to communicate with WS2812.  
```
typedef struct {
    union {
        struct {
            uint32_t duration0 :15;
            uint32_t level0 :1;
            uint32_t duration1 :15;
            uint32_t level1 :1;
        };
        uint32_t val;
    };
} rmt_data_t;
```  
`ESP32_LED(r,g,b)` invokes `ws2812.setLedColor(0, r, g, b)`, which eventually invokes:  
```
esp_err_t Freenove_ESP32_WS2812::set_pixel(int index, u8 r, u8 g, u8 b)
{
        u32 color = r << 16 | g << 8 | b ;
        for (int bit = 0; bit < 24; bit++) {
                if (color & (1 << (23-bit))) {
                        led_data[index*24+bit].level0 = 1;
                        led_data[index*24+bit].duration0 = 8;
                        led_data[index*24+bit].level1 = 0;
                        led_data[index*24+bit].duration1 = 4;
                } else {
                        led_data[index*24+bit].level0 = 1;
                        led_data[index*24+bit].duration0 = 4;
                        led_data[index*24+bit].level1 = 0;
                        led_data[index*24+bit].duration1 = 8;
                }
        }
        return ESP_OK;
}
```
... where `led_data[]` is written by `show()`:  `return rmtWrite(rmt_send, led_data, ledCounts*24);`,  
declared in [`esp32-hal-rmt.h`](https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/esp32-hal-rmt.h),  
indicating that ESP32's Remote Control Peripheral ([RMT](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/rmt.html)) is
[employed](https://demo-dijiudu.readthedocs.io/en/latest/api-reference/peripherals/rmt.html).  
It gets chapter 14 in the [ESP32 Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf).  
Here is a [MicroPython reference for RMT](https://pycom.github.io/pydocs/tutorials/all/rmt.html).  
   
Here is [GitHub ESP32-NeoPixel-WS2812-RMT driver example code](https://github.com/JSchaenzle/ESP32-NeoPixel-WS2812-RMT), using the same 4x24 bytes per LED.   
According to this [GitHub esp32_digitalLEDs README](https://github.com/CalinRadoni/esp32_digitalLEDs), this memory abuse was/is a driver limitation;  
[This later ESP32 DLED Controller implementation claims to be faster and more efficient](https://github.com/CalinRadoni/ESP32DLEDController).  

According to [this protocol description](https://www.arrow.com/en/research-and-events/articles/protocol-for-the-ws2812b-programmable-led),
each WS2812B chip wants only 24bits, but ESP32's [FreeRTOS](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html)
implementation employs 24 32-bit words, for terrifically inefficient bit-banging.  

Here is [an independent documentation of ESP32 RMT hacking](https://www.buildlog.net/blog/2017/11/esp32-sending-short-pulses-with-the-rmt).  

[What is FreeRTOS? (ESP32 + Arduino series)](https://www.youtube.com/watch?v=kP-pP6FEu8I) YouTube video  
Here is [another introductory video for  FreeRTOS (ESP32 + Arduino series)](https://www.youtube.com/watch?v=WQGAs9MwXno).  

