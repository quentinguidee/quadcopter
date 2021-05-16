ARDUINO_CLI=arduino-cli

OS := $(shell uname)
ifeq ($(OS), Darwin)
PORT=/dev/tty.usbmodem14201
else
PORT=/dev/ttyACM0
endif

ifndef TARGET
TARGET=arduino
endif

ifeq ($(TARGET), arduino)
BOARD=arduino:avr:mega:cpu=atmega2560
FILE=quadcopter.ino
else
BOARD=esp8266:esp8266:generic
FILE=esp8266/esp8266.ino
endif


compile:
	${ARDUINO_CLI} -b ${BOARD} compile ${FILE}

install:
	${ARDUINO_CLI} core update-index
	${ARDUINO_CLI} core install arduino:avr
	${ARDUINO_CLI} core install esp8266:esp8266
	${ARDUINO_CLI} lib install MPU9250_asukiaaa
	${ARDUINO_CLI} lib install RunningMedian
	${ARDUINO_CLI} lib install "Adafruit NeoPixel"
	${ARDUINO_CLI} lib install --git-url https://github.com/me-no-dev/ESPAsyncTCP.git
	${ARDUINO_CLI} lib install --git-url https://github.com/me-no-dev/ESPAsyncWebServer.git

upload:
	${ARDUINO_CLI} -b ${BOARD} -p ${PORT} upload ${FILE}
