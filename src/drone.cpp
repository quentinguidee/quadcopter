#include "drone.h"

#include "interface/interface.h"
#include "sensors/accelerometer.h"

Drone::Drone() :
    accelerometer(Accelerometer()),
    piezo(Piezo((uint8_t)PIEZO_PIN)),
    bluetooth(Bluetooth()),
    position(Position(accelerometer)),
    statusLed(RGBLed((uint8_t)STATUS_LED_RED_PIN, (uint8_t)STATUS_LED_GREEN_PIN, (uint8_t)STATUS_LED_BLUE_PIN)),
    onOffButton(ToggleButton((uint8_t)POWER_TOGGLE_BUTTON_PIN))
{
    Interface::setup(this);
}

Drone::~Drone()
{
}

void Drone::setup()
{
    for (uint8_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].registerLed(&leds[i]);
        motors[i].setup();
    }
    onOffButton.setup();
    statusLed.setup();
    statusLed.setColor(255, 0, 0);
}

void Drone::startup()
{
    statusLed.setColor(255, 255, 0);
    accelerometer.startup();
    for (uint8_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].startup();
    }
    piezo.startup();
    statusLed.setColor(0, 255, 0);
}

void Drone::shutdown()
{
    statusLed.setColor(255, 255, 0);
    for (uint8_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].shutdown();
    }
    piezo.shutdown();
    statusLed.setColor(255, 0, 0);
}

void Drone::tick()
{
    onOffButton.tick();
    if (onOffButton.getHasChanged())
    {
        onOffButton.isOn() ? startup() : shutdown();
    }
    else if (onOffButton.isOn())
    {
        accelerometer.tick();
        position.update();
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
        piezo.on(1000, 100);
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
