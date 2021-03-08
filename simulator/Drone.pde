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
        background(0);
        
        pushMatrix();
        translate(width / 2, height - 100, 0);
        rotateY(0);
        stroke(0xff888888);
        noFill();
        box(50, 2, 50);
        popMatrix();
    }
}
