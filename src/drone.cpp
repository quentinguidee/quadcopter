#include "drone.h"

#include "interface/interface.h"
#include "interface/simulator.h"
#include "utils/log.h"

Drone::Drone() :
    accelerometer(Accelerometer()),
    altimeter(Altimeter()),
    onOffButton(ToggleButton((uint8_t)POWER_TOGGLE_BUTTON_PIN)),
    position(Position(accelerometer)),
    flightController(FlightController()),
    status(Status::off),
    serialResponseBuffer(""),
    lastPingTimestamp(0),
    lastTrackingSending(0),
    timer(millis()),
    simulatorLed(Led((uint8_t)LED_SIMULATOR_PIN))
{
    Interface::setup(this);
}

Drone::~Drone()
{
}

void Drone::setup()
{
    onOffButton.setup();
    simulatorLed.setup();

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
    timer = millis();
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

    if (onOffButton.isOn())
    {
        if (millis() - lastTrackingSending > 200)
        {
            // A/B/C = accelerations
            // D/E/F = anglesSpeed
            // G/H/I = angles
            Serial1.println(String("@A") + accelerometer.getAccelerationX() + "B" + accelerometer.getAccelerationY() + "C" + accelerometer.getAccelerationZ() + "D" + accelerometer.getAngleSpeedX() + "E" + accelerometer.getAngleSpeedY() + "F" + accelerometer.getAngleSpeedZ() + "G" + position.getAngleX() + "H" + position.getAngleY() + "I" + position.getAngleZ());
            if (isInSimMode)
            {
                Simulator::send(String("#A") + accelerometer.getAccelerationX() + "B" + accelerometer.getAccelerationY() + "C" + accelerometer.getAccelerationZ() + "D" + accelerometer.getAngleSpeedX() + "E" + accelerometer.getAngleSpeedY() + "F" + accelerometer.getAngleSpeedZ() + "G" + position.getAngleX() + "H" + position.getAngleY() + "I" + position.getAngleZ());
            }
            lastTrackingSending = millis();
        }

        accelerometer.tick();
        altimeter.tick();
        position.update();
        flightController.tick(
            position.getAngleX(),
            position.getAngleY(),
            position.getAngleZ(),
            altimeter.getZ(),
            accelerometer.getAngleSpeedX(),
            accelerometer.getAngleSpeedY(),
            accelerometer.getAngleSpeedZ(),
            altimeter.getRateZ());

        float altitudeRate = flightController.getPIDAltitudeRate().getOutput();
        float angleRateX = flightController.getPIDAngleRateX().getOutput();
        float angleRateY = flightController.getPIDAngleRateY().getOutput();
        float angleRateZ = flightController.getPIDAngleRateZ().getOutput();

        motors[0].setSpeed(altitudeRate /*  + angleRateX - angleRateY + angleRateZ */);
        motors[1].setSpeed(altitudeRate /*  - angleRateX - angleRateY - angleRateZ */);
        motors[2].setSpeed(altitudeRate /* + angleRateX + angleRateY - angleRateZ */);
        motors[3].setSpeed(altitudeRate /*  - angleRateX + angleRateY + angleRateZ */);

        if (isInSimMode)
        {
            Simulator::sendMotorSpeed(
                motors[0].getSpeed(),
                motors[1].getSpeed(),
                motors[2].getSpeed(),
                motors[3].getSpeed(),
                millis() - timer);
        }

        timer = millis();
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

void Drone::enableSimulatorMode()
{
    if (status != off)
    {
        // Cannot enable sim mode during flight.
        return;
    }

    isInSimMode = true;
    simulatorLed.on();

    accelerometer.enableSimMode();
    altimeter.enableSimMode();

    for (uint8_t i = 0; i < MOTORS_COUNT; i++)
    {
        motors[i].enableSimMode();
        leds[i].enableSimMode();
        leds[i].on();
    }

    Simulator::callbackSimModeEnabled();
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
    else
    {
        buffer += character;
        return false;
    }
}
