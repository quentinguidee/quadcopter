BOARD=arduino:avr:mega:cpu=atmega2560

OS := $(shell uname)
ifeq ($(OS), Darwin)
PORT=/dev/tty.usbmodem14201
else
PORT=/dev/ttyACM0
endif

all:
	arduino-cli -b ${BOARD} compile

install:
	arduino-cli core install arduino:avr
	arduino-cli lib install MPU9250_asukiaaa
	arduino-cli lib install RunningMedian

upload:
	arduino-cli -b ${BOARD} -p ${PORT} upload
