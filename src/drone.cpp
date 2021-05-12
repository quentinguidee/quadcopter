#include "drone.h"

#include "interface/interface.h"
#include "interface/send.h"
#include "interface/simulator.h"
#include "utils/log.h"

Drone::Drone() :
    motors(Motors()),
    leds(Leds()),
    accelerometer(Accelerometer()),
    altimeter(Altimeter()),
    onOffButton(ToggleButton((uint8_t)Settings::POWER_TOGGLE_BUTTON_PIN)),
    position(Position(accelerometer)),
    flightController(FlightController()),
    status(Status::off),
    serialResponseBuffer(""),
    lastPingTimestamp(0),
    lastTrackingSending(0),
    timer(millis()),
    simulatorLed(Led((uint8_t)Settings::LED_SIMULATOR_PIN))
{
    Interface::setup(this);
}

Drone::~Drone()
{
}

void Drone::armOnOffButton()
{
    onOffButton.startup();
}

void Drone::startup()
{
    setStatus(Status::inStartup);

    simulatorLed.startup();
    leds.startup();
    motors.startup();
    accelerometer.startup();
    flightController.startup();

    timer = millis();

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

        // flightController.tick(
        //     position.getAngleX(),
        //     position.getAngleY(),
        //     position.getAngleZ(),
        //     accelerometer.getAngleSpeedX(),
        //     accelerometer.getAngleSpeedY(),
        //     accelerometer.getAngleSpeedZ(),
        //     altimeter.getZ());

        // float altitudeRate = flightController.getPIDAltitude().getOutput();
        // float angleRateX = flightController.getPIDAngleRateX().getOutput();
        // float angleRateY = flightController.getPIDAngleRateY().getOutput();
        // float angleRateZ = flightController.getPIDAngleRateZ().getOutput();

        // float motorASpeed = 119 + altitudeRate /* + angleRateX - angleRateY + angleRateZ */;
        // float motorBSpeed = 119 + altitudeRate /* - angleRateX - angleRateY - angleRateZ */;
        // float motorCSpeed = 119 + altitudeRate /* + angleRateX + angleRateY - angleRateZ */;
        // float motorDSpeed = 119 + altitudeRate /* - angleRateX + angleRateY + angleRateZ */;

        // motors.get(0).setSpeed(motorASpeed < 30 ? 30 : motorASpeed);
        // motors.get(1).setSpeed(motorBSpeed < 30 ? 30 : motorBSpeed);
        // motors.get(2).setSpeed(motorCSpeed < 30 ? 30 : motorCSpeed);
        // motors.get(3).setSpeed(motorDSpeed < 30 ? 30 : motorDSpeed);

        // if (isInSimMode)
        // {
        //     Simulator::sendMotorSpeed(
        //         motors.get(0).getSpeed(),
        //         motors.get(1).getSpeed(),
        //         motors.get(2).getSpeed(),
        //         motors.get(3).getSpeed(),
        //         millis() - timer);
        // }

        timer = millis();
        checkSecurity();
    }

    onOffButton.tick();
    motors.tick();
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
    motors.enableSimMode();
    leds.enableSimMode();

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

    buffer += character;
    return false;
}
