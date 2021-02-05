#include "drone.h"

#include "interface/interface.h"
#include "sensors/accelerometer.h"

Drone::Drone() :
    accelerometer(Accelerometer()),
    wifi(Wifi()),
    statusLed(JewelLed((uint8_t)JEWEL_LED_PIN)),
    onOffButton(ToggleButton((uint8_t)POWER_TOGGLE_BUTTON_PIN)),
    position(Position(accelerometer)),
    flightController(FlightController()),
    status(Status::off)
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
    setStatus(Wifi::init);
    wifi.setup();
    setStatus(wifi.getStatus());
    setStatus(Status::off);

    for (uint8_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].setup();
        setStatus(motors[i].getStatus(), i);
    }
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
        for (uint8_t i = 0; i < MOTORS_COUNT; i++)
        {
            motors[i].tick();
        }
    }
    else
    {
        delay(100);
    }
}

void Drone::checkSecurity()
{
}

Motor& Drone::getMotor(Motor::Position position)
{
    return motors[(int)position];
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
        case Wifi::Status::off:
            statusLed.off(0);
            break;

        case Wifi::Status::init:
            statusLed.on(0, Color::red);
            break;

        case Wifi::Status::connected:
            statusLed.off(0);
            break;

        case Wifi::Status::error:
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
        statusLedID = motorID + 1;
    }
    else
    {
        statusLedID = motorID + 2;
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
