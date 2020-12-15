all:
	arduino-cli -b arduino:avr:uno compile

install:
	arduino-cli core install arduino:avr

upload:
	arduino-cli -b arduino:avr:uno -p /dev/ttyACM0 upload
