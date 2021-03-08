import processing.serial.*;

public class Drone {
    Serial port;
    String buffer;
    
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
            println("|||||||||| (Success) SimMode enabled");
        }
    }
    
    private void simModeEnabledCallback() {
        enableSimModeButton.setColorBackground(0xff222222);
        enableSimModeButton.setColorActive(0xff222222);
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
        pushMatrix();
        translate(width / 2 - 25, height - 100, 0 - 25);
        rotateY(0);
        noStroke();
        fill(0xff0000ff);
        box(4, 4, 4);
        popMatrix();
        
        pushMatrix();
        translate(width / 2 + 25, height - 100, 0 - 25);
        rotateY(0);
        noStroke();
        fill(0xff0000ff);
        box(4, 4, 4);
        popMatrix();
        
        pushMatrix();
        translate(width / 2 - 25, height - 100, 0 + 25);
        rotateY(0);
        noStroke();
        fill(0xffff0000);
        box(4, 4, 4);
        popMatrix();
        
        pushMatrix();
        translate(width / 2 + 25, height - 100, 0 + 25);
        rotateY(0);
        noStroke();
        fill(0xffff0000);
        box(4, 4, 4);
        popMatrix();
    }
}
