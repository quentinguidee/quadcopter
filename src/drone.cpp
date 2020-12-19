#include "drone.h"

#include "interface/interface.h"
#include "sensors/accelerometer.h"

Drone::Drone() :
    accelerometer(Accelerometer()),
    piezo(Piezo((uint8_t)PIEZO_PIN)),
    bluetooth(Bluetooth()),
    position(Position(accelerometer)),
    statusLed(RGBLed((uint8_t)STATUS_LED_RED_PIN, (uint8_t)STATUS_LED_GREEN_PIN, (uint8_t)STATUS_LED_BLUE_PIN))
{
    Interface::setup(this);
}

Drone::~Drone()
{
}

void Drone::setup()
{
    statusLed.setup();
    statusLed.setColor(255, 0, 0);
    accelerometer.setup();
    piezo.setup();
    for (uint8_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].registerLed(&leds[i]);
        motors[i].setup();
    }
    statusLed.setColor(0, 255, 0);
}

void Drone::startup()
{
    for (uint8_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].startup();
    }
}

void Drone::shutdown()
{
    for (uint8_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].shutdown();
    }
}

void Drone::tick()
{
    accelerometer.tick();
    position.update();
    piezo.tick();
    for (uint8_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].tick();
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
