import processing.serial.*;

public class Drone {
    Serial port;
    String buffer;
    
    boolean isOn = false;
    
    boolean[] ledsState = { false, false, false, false };
    
    public Drone(Serial port) {
        this.port = port;
    }
    
    public Serial getPort() {
        return port;
    }
    
    public void tick() {
        readSerial();
        draw();
    }
    
    private void readSerial() {
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
    
    private void onCommandReceived(String buffer) {
        println("[RECEIVED] " + buffer);
        char category = buffer.charAt(1);
        if (category == 'S') {
            simModeEnabledCallback();
            println("|||||||||| SimMode enabled");
        } else if (category == 'L') {
            int led = Integer.parseInt(str(buffer.charAt(2)));
            boolean action = boolean(Integer.parseInt(str(buffer.charAt(3))));
            println("|||||||||| LED " + led + " set to " + action);
            ledsState[led] = action;
        }
    }
    
    private void simModeEnabledCallback() {
        enableSimModeButton.setColorBackground(0xff222222);
        enableSimModeButton.setColorActive(0xff222222);
        isOn = true;
    }
    
    private void draw() {
        background(0xff111111);
        
        pushMatrix();
        translate(width / 2, height - 100, 0);
        rotateY(0);
        stroke(0xff888888);
        noFill();
        box(50, 2, 50);
        popMatrix();
        
        drawLEDs();
    }
    
    private void drawLEDs() {
        if (ledsState[0]) {
            pushMatrix();
            translate(width / 2 - 25, height - 100, 0 - 25);
            rotateY(0);
            noStroke();
            fill(0xff0000ff);
            box(4, 4, 4);
            popMatrix();
        }
        
        if (ledsState[1]) {
            pushMatrix();
            translate(width / 2 + 25, height - 100, 0 - 25);
            rotateY(0);
            noStroke();
            fill(0xff0000ff);
            box(4, 4, 4);
            popMatrix();
        }
        
        if (ledsState[2]) {
            pushMatrix();
            translate(width / 2 - 25, height - 100, 0 + 25);
            rotateY(0);
            noStroke();
            fill(0xffff0000);
            box(4, 4, 4);
            popMatrix();
        }
        
        if (ledsState[3]) {
            pushMatrix();
            translate(width / 2 + 25, height - 100, 0 + 25);
            rotateY(0);
            noStroke();
            fill(0xffff0000);
            box(4, 4, 4);
            popMatrix();
        }
    }
}
