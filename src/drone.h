#ifndef DRONE_H
#define DRONE_H

#include "components/accelerometer.h"
#include "components/altimeter.h"
#include "components/led.h"
#include "components/motor.h"
#include "components/toggle_button.h"
#include "flight_controller.h"
#include "leds.h"
#include "motors.h"
#include "position.h"
#include "settings.h"
#include "utils/wifi.h"

class Drone
{
public:
    enum Status
    {
        off,
        inStartup,
        ready,
        on,
        inShutdown
    };

private:
    Motors motors;
    Leds leds;

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

    bool onSerialRead(char character, String& buffer);

public:
    Drone();
    ~Drone();

    void setup();
    void startup();
    void shutdown();

    void tick();

    void readSerials();
    void checkSecurity();
    void handleOnOffButtonStateChanged();
    void ping();

    Motors& getMotors() { return motors; }
    Accelerometer& getAccelerometer() { return accelerometer; }
    Altimeter& getAltimeter() { return altimeter; }
    ToggleButton& getOnOffButton() { return onOffButton; }
    FlightController& getFlightController() { return flightController; }

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
