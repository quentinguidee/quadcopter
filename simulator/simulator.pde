import processing.serial.*;

Serial port;

void setup() {
    port = new Serial(this, Serial.list()[3], 38400);
    delay(2000);
    port.write("$S\n");
}

void draw() {
}
