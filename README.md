# Quadcopter

An Arduino quadcopter.

Screenshot of the [client](https://github.com/quentinguidee/quadcopter-client):

![drone](https://user-images.githubusercontent.com/12123721/117687144-c8bea180-b1b7-11eb-8b94-648ac7e832aa.png)

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

## Communications

![flow](https://user-images.githubusercontent.com/12123721/117688496-1ab3f700-b1b9-11eb-81f0-71072ee6884c.png)

## License

This project is released under the [MIT license](./LICENSE.md).
