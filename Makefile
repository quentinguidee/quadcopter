BOARD=arduino:avr:mega:cpu=atmega2560

all:
	arduino-cli -b ${BOARD} compile

install:
	arduino-cli core install arduino:avr
	arduino-cli lib install MPU9250_asukiaaa

upload:
	arduino-cli -b ${BOARD} -p /dev/ttyACM0 upload
