#ifndef Servo_h
#define Servo_h

#define TIMER_INTERRUPT_DEBUG       0
#define ISR_SERVO_DEBUG             1

// Select different ESP32 timer number (0-3) to avoid conflict
#define USE_ESP32_TIMER_NO          3

#include "ESP32_S2_ISR_Servo.h"		// declares `extern ESP32_ISR_Servo ESP32_ISR_Servos;` to control up to 16 servos

class Servo
{
public:
  Servo();
  uint8_t attach(int pin);           // attach pin to the next free channel, sets pinMode, returns channel number or 0 if failure
  uint8_t attach(int pin, int min, int max); // as above but also sets min and max values for writes.
  void detach();
  void write(int value); 
  int read();                        // returns current pulse width
private:
   uint8_t servoIndex;               // index into the channel data for this servo
   int8_t min;                       // minimum is this value times 4 added to MIN_PULSE_WIDTH
   int8_t max;                       // maximum is this value times 4 added to MAX_PULSE_WIDTH
};

// Map Arduino pins to available ESP32-S2 PWM pins
#define PC13 2				// typical LED pin:  GPIO0
#define WS2812_PIN  18  		// GPIO18 for ESP32-S2-Saola-1M (WROOM)
// 8,9 are SDA, SCL; 15-16 are XTAL; 17 is DAC1; 19-20 are USB; 22-25 are nc
// 26 is Flash; 27-32 are nc; 39-42 are JTAG; 43-44 are COM port; 46 is input-only
#define PB9  6
#define PB8  7
#define PB7  10
#define PB6  11
#define PA10 12
#define PA9  13
#define PA8  14
#define PB1  21
#define PB0  33
#define PA7  34
#define PA6  35
#define PA3  36
#define PA2  37
#define PA1  38
#define PA15 45


#endif
