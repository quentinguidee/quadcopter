#ifndef DRONE_H
#define DRONE_H

#include "components/led.h"
#include "components/motor.h"
#include "components/piezo.h"
#include "sensors/accelerometer.h"
#include "settings.h"

#define MOTORS_COUNT 4

class Drone
{
private:
    Motor motors[MOTORS_COUNT] = {
        Motor((uint8_t)ESC_MOTOR_A_PIN),
        Motor((uint8_t)ESC_MOTOR_B_PIN),
        Motor((uint8_t)ESC_MOTOR_C_PIN),
        Motor((uint8_t)ESC_MOTOR_D_PIN),
    };
    Accelerometer accelerometer;
    Led leds[MOTORS_COUNT] = {
        Led((uint8_t)LED_MOTOR_A_PIN),
        Led((uint8_t)LED_MOTOR_B_PIN),
        Led((uint8_t)LED_MOTOR_C_PIN),
        Led((uint8_t)LED_MOTOR_D_PIN),
    };
    Piezo piezo;

public:
    Drone();
    ~Drone();

    void setup();
    void startup();
    void shutdown();

    void tick();

    Motor& getMotor(Motor::Position position);
    Motor& getMotor(int8_t index);
    Accelerometer& getAccelerometer() { return accelerometer; }
    Piezo& getPiezo() { return piezo; }
};

#endif /* DRONE_H */
