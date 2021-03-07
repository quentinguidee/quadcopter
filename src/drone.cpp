#include "drone.h"

#include "interface/interface.h"
#include "sensors/accelerometer.h"
#include "utils/log.h"

Drone::Drone() :
    accelerometer(Accelerometer()),
    onOffButton(ToggleButton((uint8_t)POWER_TOGGLE_BUTTON_PIN)),
    position(Position(accelerometer)),
    flightController(FlightController()),
    status(Status::off),
    serialResponseBuffer(""),
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
    onOffButton.setup();
    setStatus(Status::off);

    for (uint8_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].setup();
        leds[i].setup();
        leds[i].on();
    }
    Serial.println("START");
}

void Drone::startup()
{
    setStatus(Status::inStartup);
    accelerometer.startup();
    for (uint8_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].startup();
    }
    flightController.startup();
    setStatus(Status::on);
}

void Drone::shutdown()
{
    setStatus(Status::inShutdown);
    for (uint8_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].shutdown();
    }
    setStatus(Status::off);
}

void Drone::tick()
{
    while (Serial1.available())
    {
        char c = Serial1.read();
        if (c == '\n' && serialResponseBuffer != "")
        {
            if (serialResponseBuffer[0] == '$')
            {
                Interface::execute(serialResponseBuffer);
            }
            serialResponseBuffer = "";
        }
        else
        {
            serialResponseBuffer += c;
        }
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

    if (onOffButton.isOn())
    {
        if (millis() - lastTrackingSending > 200)
        {
            // A/B/C = accelerations
            // D/E/F = anglesSpeed
            // G/H/I = angles
            Serial1.println(String("@A") + accelerometer.getAccelerationX() + "B" + accelerometer.getAccelerationY() + "C" + accelerometer.getAccelerationZ() + "D" + accelerometer.getAngleSpeedX() + "E" + accelerometer.getAngleSpeedY() + "F" + accelerometer.getAngleSpeedZ() + "G" + position.getAngleX() + "H" + position.getAngleY() + "I" + position.getAngleZ());
            lastTrackingSending = millis();
        }

        accelerometer.tick();
        position.update();
        flightController.tick(
            position.getAngleX(),
            position.getAngleY(),
            position.getAngleZ(),
            accelerometer.getAngleSpeedX(),
            accelerometer.getAngleSpeedY(),
            accelerometer.getAngleSpeedZ());

        checkSecurity();
    }

    onOffButton.tick();

    for (uint8_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].tick();
    }
}

void Drone::checkSecurity()
{
}

void Drone::ping()
{
    lastPingTimestamp = millis();
}

Motor& Drone::getMotor(int8_t index)
{
    return motors[index];
}

void Drone::setStatus(Status status)
{
    this->status = status;
}
