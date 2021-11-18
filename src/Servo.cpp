// Wrap ESP32-S2 ESP32_S2_ISR_Servo for generic Arduino Servo sketches

// for ESP32_S2_ISR_Servo.h
#define TIMER_INTERRUPT_DEBUG   0
#define ISR_SERVO_DEBUG         1

// Select ESP32 timer number (0-3) to avoid conflict
#define USE_ESP32_TIMER_NO      3       // as used in libraries/ESP32_S2_ISR_Servo

// declares `extern ESP32_ISR_Servo ESP32_ISR_Servos;` for up to 16 servos
#include "ESP32_S2_ISR_Servo.h"         // defines MIN_PULSE_WIDTH, MAX_PULSE_WIDTH 

#include "Servo.h"

Servo::Servo() {
    this->resetFields();
ESP32_ISR_Servos.useTimer(USE_ESP32_TIMER_NO);
}

uint8_t Servo::attach(uint8_t pin, uint16_t minPW, uint16_t maxPW, int16_t minAngle, int16_t maxAngle)
{
    this->pin = pin;
    this->minPW = minPW;
    this->maxPW = maxPW;
    this->minAngle = minAngle;
    this->maxAngle = maxAngle;
    this->servoIndex = ESP32_ISR_Servos.setupServo(pin, minPW, maxPW);

    return this->servoIndex;
}

uint8_t Servo::attach(uint8_t pin, uint16_t minPW, uint16_t maxPW)
{
  return this->attach(pin, minPW, maxPW, MIN_ANGLE, MAX_ANGLE);
}

uint8_t Servo::attach(uint8_t pin)
{
  return this->attach(pin, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
}

void Servo::detach() {
    this->resetFields();
}

void Servo::write(int degrees) {
    degrees = constrain(degrees, this->minAngle, this->maxAngle);
    ESP32_ISR_Servos.setPosition(this->servoIndex, degrees);
}

int Servo::read() {
    return ESP32_ISR_Servos.getPosition(this->servoIndex);
}

void Servo::writeMicroseconds(uint16_t pulseWidth) {
    if (this->attached())
        ESP32_ISR_Servos.setPulseWidth(this->servoIndex, pulseWidth);
}

uint16_t Servo::readMicroseconds() {
    if (!this->attached()) {
        return 0;
    }
    return ESP32_ISR_Servos.getPulseWidth(this->servoIndex);
}

void Servo::resetFields(void) {
    this->pin = NOT_ATTACHED;
    this->minAngle = MIN_ANGLE;
    this->maxAngle = MAX_ANGLE;
    this->minPW = MIN_PULSE_WIDTH;
    this->maxPW = MAX_PULSE_WIDTH;
}

