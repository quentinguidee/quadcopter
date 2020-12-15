all:
	arduino-cli -b arduino:avr:uno compile

install:
	arduino-cli core install arduino:avr
	arduino-cli lib install MPU9250_asukiaaa

upload:
	arduino-cli -b arduino:avr:uno -p /dev/ttyACM0 upload
