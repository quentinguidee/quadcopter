import processing.serial.*;
import controlP5.*;

ControlP5 ui;

Serial port;
String buffer;

// UI
Button enableSimModeButton;

Slider2D acceleration;
Slider2D angleRate;
Slider2D angle;

void setup() {
    port = new Serial(this, Serial.list()[3], 38400);
    
    // UI
    size(1600, 656, P3D);
    surface.setTitle("Quadcopter");
    surface.setResizable(true);
    
    ui = new ControlP5(this);
    
    Group sidebar = ui.addGroup("sidebar")
       .setPosition(0, 0)
       .setColorBackground(0xff111111);
    
    enableSimModeButton = ui.addButton("enableSimMode")
       .setPosition(0, 0)
       .setSize(200, 26)
       .setCaptionLabel("Enable Sim Mode")
       .setGroup(sidebar);
}

void draw() {
    while(port.available() > 0) {
        char character = port.readChar();
        if (character == '\n' && buffer != "") {
            if (buffer.charAt(0) == '#') {
                onCommandReceived(buffer);
            }
            buffer = "";
        } else {
            buffer += character;
        }
    }
    
    background(0);
    
    pushMatrix();
    translate(width / 2, height - 100, 0);
    rotateY(0);
    stroke(0xff888888);
    noFill();
    box(50, 2, 50);
    popMatrix();
}

void onCommandReceived(String buffer) {
    println("[RECEIVED] " + buffer);
    char category = buffer.charAt(1);
    if (category == 'S') {
        simModeEnabledCallback();
        println("|||||||||| (Success) SimMode enabled");
    }
}

public void enableSimMode() {
    port.write("$S\n");
}

public void simModeEnabledCallback() {
    enableSimModeButton.setColorBackground(0xff222222);
    enableSimModeButton.setColorActive(0xff222222);
}
