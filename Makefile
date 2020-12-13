all:
	arduino-cli -b arduino:avr:uno compile

install:
	arduino-cli core install arduino:avr
