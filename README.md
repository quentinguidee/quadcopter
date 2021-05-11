# Quadcopter

An Arduino quadcopter with a simulator written in Processing.

| WARNING | The code is currently not usable without modifications. |
| ------- | ------------------------------------------------------- |

## Install

1. Install [arduino-cli](https://github.com/arduino/arduino-cli).
2. Install the dependencies:

```bash
make install
```

3. Build and transfer the program to the Arduino:

```bash
make compile TARGET=arduino
make upload TARGET=arduino
```

4. Build and transfer the program to the ESP8266:

```bash
make compile TARGET=esp8266
make upload TARGET=esp8266
```

## Simulator

The simulator will simulate a 3D environment for the drone to move. The drone must be turned on and plugged in for the simulator to work, because he remains in charge of the calculations. The simulator takes care of the 3D environment and makes him believe that he's moving in this space while recovering his telemetry.

To run the simulator, install `processing-java`. Then:

```bash
make sim
```

## License

This project is released under the [MIT license](./LICENSE.md).
