#ifndef DRONE_H
#define DRONE_H

#include "components/jewel_led.h"
#include "components/motor.h"
#include "components/toggle_button.h"
#include "flight_controller.h"
#include "position.h"
#include "sensors/accelerometer.h"
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
    Accelerometer accelerometer;
    JewelLed statusLed;
    ToggleButton onOffButton;

    Position position;
    FlightController flightController;

    Status status;

    String serialResponseBuffer;

    unsigned long lastPingTimestamp;
    unsigned long lastTrackingSending;

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
    // Wifi& getWifi() { return wifi; }
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

    void setStatus(Wifi::Status status);
    void setStatus(Motor::Status status, uint8_t motorID);
};

#endif /* DRONE_H */
