import processing.serial.*;
import controlP5.*;

ControlP5 ui;

Serial port;
String buffer;

void setup() {
    port = new Serial(this, Serial.list()[3], 38400);
    
    // UI
    size(800, 400);
    noStroke();
    ui = new ControlP5(this);
    ui.addButton("enableSimMode")
       .setValue(0)
       .setPosition(0, 0)
       .setSize(200, 26)
       .setCaptionLabel("Enable Sim Mode");
}

public void enableSimMode(int val) {
    println(val);
    port.write("$S\n");
}
