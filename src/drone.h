#ifndef DRONE_H
#define DRONE_H

#include "components/accelerometer.h"
#include "components/altimeter.h"
#include "components/led.h"
#include "components/motor.h"
#include "components/toggle_button.h"
#include "flight_controller.h"
#include "position.h"
#include "settings.h"
#include "utils/wifi.h"

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
        Motor(0, (uint8_t)ESC_MOTOR_A_PIN),
        Motor(1, (uint8_t)ESC_MOTOR_B_PIN),
        Motor(2, (uint8_t)ESC_MOTOR_C_PIN),
        Motor(3, (uint8_t)ESC_MOTOR_D_PIN),
    };
    Led leds[MOTORS_COUNT] = {
        Led((uint8_t)LED_MOTOR_A_PIN),
        Led((uint8_t)LED_MOTOR_B_PIN),
        Led((uint8_t)LED_MOTOR_C_PIN),
        Led((uint8_t)LED_MOTOR_D_PIN),
    };
    Led simulatorLed;
    Accelerometer accelerometer;
    Altimeter altimeter;
    ToggleButton onOffButton;

    Position position;
    FlightController flightController;

    Status status;

    String serialResponseBuffer;
    String serial1ResponseBuffer;

    unsigned long lastPingTimestamp;
    unsigned long lastTrackingSending;
    unsigned long timer;

    bool isInSimMode = false;

    bool onSerialRead(char character, String& buffer);

public:
    Drone();
    ~Drone();

    void setup();
    void startup();
    void shutdown();

    void tick();
    void checkSecurity();
    void ping();

    Motor& getMotor(int8_t index);
    Accelerometer& getAccelerometer() { return accelerometer; }
    Altimeter& getAltimeter() { return altimeter; }
    ToggleButton& getOnOffButton() { return onOffButton; }

    Position& getPosition() { return position; }

    // Status
    void setStatus(Status status);
    Status getStatus() { return status; }
    bool isOn() { return status == Status::on; }
    bool isInStartup() { return status == Status::inStartup; }
    bool isOff() { return status == Status::off; }
    bool isShutdown() { return status == Status::inShutdown; }

    void enableSimulatorMode();
};

#endif /* DRONE_H */
