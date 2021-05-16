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
    status(Status::off),
    serialResponseBuffer(""),
    lastPingTimestamp(0),
    lastTrackingSending(0),
    simulatorLed(Led(Settings::LED_SIMULATOR_PIN))
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
    onOffButton.startup();
}

void Drone::startup()
{
    setStatus(Status::inStartup);

    simulatorLed.startup();
    leds.startup();
    motors.startup();
    flightController.startup();

    setStatus(Status::ready);

    Send::startupDone();
}

void Drone::shutdown()
{
    setStatus(Status::inShutdown);

    leds.shutdown();
    motors.shutdown();

    setStatus(Status::off);

    Send::shutdownDone();
}

void Drone::tick()
{
    // SAFE
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

    /*
    if (millis() - lastPingTimestamp > 2000)
    {
        // TODO: HANDLE WIFI DISCONNECTED - SECURITY MODE
    }
    else
    {
        // WIFI CONNECTED
    }
    */

    if (onOffButton.getHasChanged())
    {
        onOffButton.isOn() ? startup() : shutdown();
    }
    // END SAFE

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

        checkSecurity();
        motors.tick();
    }

    onOffButton.tick();
}

void Drone::checkSecurity()
{
}

void Drone::ping()
{
    lastPingTimestamp = millis();
}

void Drone::setStatus(Status status)
{
    this->status = status;
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
