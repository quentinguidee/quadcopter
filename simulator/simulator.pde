import processing.serial.*;
import controlP5.*;

ControlP5 ui;

Serial port;
String buffer;

// UI
Button enableSimModeButton;

void setup() {
    port = new Serial(this, Serial.list()[3], 38400);
    
    // UI
    size(800, 400);
    noStroke();
    ui = new ControlP5(this);
    enableSimModeButton = ui.addButton("enableSimMode")
       .setPosition(0, 0)
       .setSize(200, 26)
       .setCaptionLabel("Enable Sim Mode");
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
}

void onCommandReceived(String buffer) {
    println("[RECEIVED] " + buffer);
    char category = buffer.charAt(1);
    if (category == 'S') {
        simModeEnabledCallback();
    }
}

public void enableSimMode() {
    port.write("$S\n");
}

public void simModeEnabledCallback() {
    enableSimModeButton.setColorBackground(0xff222222);
    enableSimModeButton.setColorActive(0xff222222);
}
