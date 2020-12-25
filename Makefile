BOARD=arduino:avr:mega:cpu=atmega2560
ARDUINO_CLI=arduino-cli

OS := $(shell uname)
ifeq ($(OS), Darwin)
PORT=/dev/tty.usbmodem14201
else
PORT=/dev/ttyACM0
endif

all:
	${ARDUINO_CLI} -b ${BOARD} compile

install:
	${ARDUINO_CLI} core install arduino:avr
	${ARDUINO_CLI} lib install MPU9250_asukiaaa
	${ARDUINO_CLI} lib install RunningMedian

upload:
	${ARDUINO_CLI} -b ${BOARD} -p ${PORT} upload
