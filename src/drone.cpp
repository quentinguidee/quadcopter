#include "drone.h"

#include "interface/interface.h"
#include "interface/send.h"
#include "utils/log.h"
#include "utils/vector4.h"

Drone::Drone() :
    motors(Motors()),
    leds(Leds()),
    accelerometer(Accelerometer()),
    altimeter(Altimeter()),
    onOffButton(ToggleButton(Settings::POWER_TOGGLE_BUTTON_PIN)),
    position(Position(accelerometer)),
    flightController(FlightController()),
    status(Status::inSetup),
    serialResponseBuffer(""),
    serial1ResponseBuffer(""),
    lastPingTimestamp(0),
    lastTrackingSending(0)
{
    Interface::setup(this);
}

Drone::~Drone()
{
}

void Drone::setup()
{
    accelerometer.startup();
    motors.setup();

    if (!motors.healthy())
    {
        setStatus(failedToSetup);
        return;
    }

    onOffButton.startup();

    setStatus(off);
}

void Drone::startup()
{
    leds.startup();
    leds.on();

    motors.startup();
    flightController.startup();

    setStatus(Status::on);
}

void Drone::shutdown()
{
    leds.shutdown();
    motors.shutdown();

    setStatus(Status::off);
}

void Drone::tick()
{
    readSerials();
    checkSecurity();
    handleOnOffButtonStateChanged();

    if (onOffButton.isOn())
    {
        // if (millis() - lastTrackingSending > 200)
        // {
        //     // A/B/C = accelerations
        //     // D/E/F = anglesSpeed
        //     // G/H/I = angles
        //     Serial1.println(String("@A") + accelerometer.getAccelerationX() + "B" + accelerometer.getAccelerationY() + "C" + accelerometer.getAccelerationZ() + "D" + accelerometer.getAngleSpeedX() + "E" + accelerometer.getAngleSpeedY() + "F" + accelerometer.getAngleSpeedZ() + "G" + position.getAngleX() + "H" + position.getAngleY() + "I" + position.getAngleZ());
        //     lastTrackingSending = millis();
        // }

        accelerometer.tick();
        altimeter.tick();
        position.update();

        Vector4<uint16_t> motorsSpeeds = flightController.tick(
            position.getAngleX(),
            position.getAngleY(),
            position.getAngleZ(),
            accelerometer.getAngleSpeedX(),
            accelerometer.getAngleSpeedY(),
            accelerometer.getAngleSpeedZ(),
            altimeter.getZ());

        motors.get(0).setSpeed(motorsSpeeds.a);
        motors.get(1).setSpeed(motorsSpeeds.b);
        motors.get(2).setSpeed(motorsSpeeds.c);
        motors.get(3).setSpeed(motorsSpeeds.d);

        motors.tick();
    }

    onOffButton.tick();
}

void Drone::readSerials()
{
    int readCount = 0;
    while (Serial.available())
    {
        bool endOfCommand = onSerialRead(Serial.read(), serialResponseBuffer);
        if (endOfCommand)
        {
            readCount++;
            if (readCount > 10) break;
        }
    }

    readCount = 0;
    while (Serial1.available())
    {
        bool endOfCommand = onSerialRead(Serial1.read(), serial1ResponseBuffer);
        if (endOfCommand)
        {
            readCount++;
            if (readCount > 10) break;
        };
    }
}

void Drone::checkSecurity()
{
    /*
    if (millis() - lastPingTimestamp > 2000)
    {
        // TODO: HANDLE WIFI DISCONNECTED - SECURITY MODE
    }
    */
}

void Drone::handleOnOffButtonStateChanged()
{
    if (onOffButton.getHasChanged())
    {
        onOffButton.isOn() ? startup() : shutdown();
    }
}

void Drone::ping()
{
    lastPingTimestamp = millis();
}

void Drone::setStatus(Status status)
{
    this->status = status;

    switch (status)
    {
        case on: Send::startupDone(); break;
        case off: Send::shutdownDone(); break;
        case setupDone: Send::setupDone(); break;
        case failedToSetup: Send::failedToSetup(); break;
    }
}

bool Drone::onSerialRead(char character, String& buffer)
{
    if (character == '\n' && buffer != "")
    {
        if (buffer[0] == '$')
        {
            Interface::execute(buffer);
        }
        buffer = "";
        return true;
    }

    buffer += character;
    return false;
}
