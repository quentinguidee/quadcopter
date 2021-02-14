#include "drone.h"

#include "interface/interface.h"
#include "sensors/accelerometer.h"
#include "utils/log.h"

Drone::Drone() :
    accelerometer(Accelerometer()),
    statusLed(JewelLed((uint8_t)JEWEL_LED_PIN)),
    onOffButton(ToggleButton((uint8_t)POWER_TOGGLE_BUTTON_PIN)),
    position(Position(accelerometer)),
    flightController(FlightController()),
    status(Status::off),
    serialResponseBuffer(""),
    lastPingTimestamp(0)
{
    Interface::setup(this);
}

Drone::~Drone()
{
}

void Drone::setup()
{
    statusLed.setup();
    onOffButton.setup();
    setStatus(Wifi::notConnected);
    setStatus(Status::off);

    for (uint8_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].setup();
        setStatus(motors[i].getStatus(), i);
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
        setStatus(motors[i].getStatus(), i);
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
        setStatus(motors[i].getStatus(), i);
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

    if (millis() - lastPingTimestamp > 2000)
    {
        setStatus(Wifi::notConnected);
    }
    else
    {
        setStatus(Wifi::connected);
    }

    for (uint8_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].tick();
        setStatus(motors[i].getStatus(), i);
    }

    onOffButton.tick();
    if (onOffButton.getHasChanged())
    {
        onOffButton.isOn() ? startup() : shutdown();
    }

    if (onOffButton.isOn())
    {
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

void Drone::setStatus(Wifi::Status status)
{
    switch (status)
    {
        case Wifi::Status::connected:
            statusLed.off(0);
            break;

        case Wifi::Status::notConnected:
            // TODO: Red blinking
            statusLed.on(0, Color::blue);
            break;
    }
}

void Drone::setStatus(Motor::Status status, uint8_t motorID)
{
    uint8_t statusLedID = 0;
    if (motorID <= 1)
    {
        statusLedID = motorID + 2;
    }
    else
    {
        statusLedID = motorID + 3;
    }

    switch (status)
    {
        case Motor::off:
            statusLed.on(statusLedID, Color::red);
            break;

        case Motor::inStartup:
            statusLed.on(statusLedID, Color::orange);
            break;

        case Motor::on:
            statusLed.on(statusLedID, Color::green);
            break;

        case Motor::inShutdown:
            statusLed.on(statusLedID, Color::orange);
            break;

        case Motor::failure:
            // TODO: Red blinking
            statusLed.on(statusLedID, Color::blue);
            break;

        default: Serial.println("[WARNING|Motor] Unhandled status case");
    }
}
