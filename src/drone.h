#ifndef DRONE_H
#define DRONE_H

#include "motor.h"
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

public:
    Drone();
    ~Drone();

    void startup();
    void shutdown();

    void tick();

    Motor& getMotor(Motor::Position position);
    Motor& getMotor(int8_t index);
    Accelerometer getAccelerometer() { return accelerometer; }
};

#endif /* DRONE_H */
