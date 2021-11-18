#ifndef Servo_h
#define Servo_h

#include <inttypes.h>

class Servo
{
  int8_t pin;

public:
#define MIN_ANGLE		0
#define MAX_ANGLE		180
#define NOT_ATTACHED		(-1)

  Servo();

  // attach pin to the next free channel, returns channel number or 0 if failure
  uint8_t attach(uint8_t pin, uint16_t min, uint16_t max, int16_t minAngle, int16_t maxAngle);
  uint8_t attach(uint8_t pin, uint16_t min, uint16_t max);
  uint8_t attach(uint8_t pin);
  bool attached() const { return this->pin != NOT_ATTACHED; }
  void detach();

  void write(int value);
  void writeMicroseconds(uint16_t pulseWidth);
  uint16_t readMicroseconds();
  int read();				// returns current pulse width

private:

   uint8_t servoIndex;			// channel for this servo
   int16_t minAngle;
   int16_t maxAngle;
   uint16_t minPW;
   uint16_t maxPW;

   void resetFields(void);
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
