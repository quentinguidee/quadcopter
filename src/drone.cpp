#include "drone.h"

#include "interface/interface.h"
#include "sensors/accelerometer.h"

Drone::Drone() :
    accelerometer(Accelerometer()),
    piezo(Piezo((uint8_t)PIEZO_PIN)),
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
    motors[0].registerJewelLed(&statusLed, 1);
    motors[1].registerJewelLed(&statusLed, 2);
    motors[2].registerJewelLed(&statusLed, 4);
    motors[3].registerJewelLed(&statusLed, 5);
    for (uint8_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].registerLed(&leds[i]);
        motors[i].setup();
    }
    onOffButton.setup();
    setStatus(Status::off);
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
    piezo.startup();
    setStatus(Status::on);
}

void Drone::shutdown()
{
    setStatus(Status::inShutdown);
    for (uint8_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].shutdown();
    }
    piezo.shutdown();
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
        piezo.tick();
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
    if (position.getAngleX() > 60 || position.getAngleX() < -60 || position.getAngleY() > 60 || position.getAngleY() < -60)
    {
        piezo.on(new int[2]{880, 1000}, 100, 2);
    }
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
