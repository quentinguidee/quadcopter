#ifndef DRONE_H
#define DRONE_H

#include "components/jewel_led.h"
#include "components/led.h"
#include "components/motor.h"
#include "components/piezo.h"
#include "components/toggle_button.h"
#include "flight_controller.h"
#include "interface/bluetooth.h"
#include "position.h"
#include "sensors/accelerometer.h"
#include "settings.h"

#define MOTORS_COUNT 4

class Drone
{
public:
    enum Status
    {
        off,
        inStartup,
        on,
        inShutdown
    };

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
    Bluetooth bluetooth;
    JewelLed statusLed;
    ToggleButton onOffButton;

    Position position;
    FlightController flightController;

    Status status;

public:
    Drone();
    ~Drone();

    void setup();
    void startup();
    void shutdown();

    void tick();
    void checkSecurity();

    Motor& getMotor(Motor::Position position);
    Motor& getMotor(int8_t index);
    Accelerometer& getAccelerometer() { return accelerometer; }
    Piezo& getPiezo() { return piezo; }
    Bluetooth& getBluetooth() { return bluetooth; }
    JewelLed& getStatusLed() { return statusLed; }
    ToggleButton& getOnOffButton() { return onOffButton; }

    Position& getPosition() { return position; }

    // Status
    void setStatus(Status status);
    Status getStatus() { return status; }
    bool isOn() { return status == Status::on; }
    bool isInStartup() { return status == Status::inStartup; }
    bool isOff() { return status == Status::off; }
    bool isShutdown() { return status == Status::inShutdown; }
};

#endif /* DRONE_H */
