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
    size(1600, 656);
    noStroke();
    ui = new ControlP5(this);
    enableSimModeButton = ui.addButton("enableSimMode")
       .setPosition(0, 0)
       .setSize(200, 26)
       .setCaptionLabel("Enable Sim Mode");
    
    ui.addTextlabel("accelerationLabel")
       .setText("Acceleration")
       .setPosition(0, 26)
       .setSize(200, 10);
    
    acceleration = ui.addSlider2D("acceleration")
       .setPosition(0, 36)
       .setColorBackground(0xff222222)
       .setSize(200, 200);
    
    ui.addTextlabel("angleRateLabel")
       .setText("Angle Rate")
       .setPosition(0, 236)
       .setSize(200, 10);
    
    angleRate = ui.addSlider2D("angleRate")
       .setPosition(0, 246)
       .setColorBackground(0xff222222)
       .setSize(200, 200);
    
    ui.addTextlabel("angleLabel")
       .setText("Angle")
       .setPosition(0, 446)
       .setSize(200, 10);
    
    angle = ui.addSlider2D("angle")
       .setPosition(0, 456)
       .setColorBackground(0xff222222)
       .setSize(200, 200);
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
