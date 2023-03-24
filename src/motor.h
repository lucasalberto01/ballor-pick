#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <stdint.h>

#define VESPA_MOTORS_CHANNEL_A 0
#define VESPA_MOTORS_CHANNEL_B 1

// --------------------------------------------------
// Class - Vespa Motors

class VespaMotors {
   public:
    VespaMotors(void);
    ~VespaMotors(void);
    void backward(uint8_t);
    void forward(uint8_t);
    void setSpeedLeft(int8_t);
    void setSpeedRight(int8_t);
    void stop(void);
    void turn(int8_t, int8_t);

    const static uint8_t FORWARD = HIGH;  // MA1 & MB1
    const static uint8_t BACKWARD = LOW;  // MA2 & MB2 (opposite of FORWARD)

   private:
    uint8_t _pinMA1, _pinMA2, _pinMB1, _pinMB2;
    uint8_t *_active_pin_A, *_active_pin_B;
    uint16_t _pwmA, _pwmB;
    uint8_t _pwm_channel_A, _pwm_channel_B;
    double _pwm_frequency;  // [Hz]
    uint8_t _pwm_resolution;
    uint16_t _max_duty_cyle;

    void _attachPin(uint8_t *);
    void _setDirectionLeft(uint8_t);
    void _setDirectionRight(uint8_t);
    void _configurePWM(void);
};

#endif