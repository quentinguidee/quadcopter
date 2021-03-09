import processing.serial.*;

public class Drone {
    Serial port;
    String buffer;
    
    boolean isOn = false;
    
    boolean[] ledsState = { false, false, false, false };
    int[] motorsRate = { 0 ,0 ,0, 0 };
    float[] position = { 0, 0, 0 }; // left-right/up-down/front-back
    
    int lastUpdate = - 1;
    float lastSpeed = 0;
    
    final float MASS = 2.0; // in kg
    final float GRAVITY = 9.81; // in m/s^2
    
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
        updatePositions();
        
        background(0xff111111);
        
        pushMatrix();
        translate(width / 2 - (position[0] * 40), height - 100 - (position[1] * 40), 0 - (position[2] * 40));
        rotateY(0);
        stroke(0xff888888);
        noFill();
        box(50, 2, 50);
        popMatrix();
        
        drawLEDs();
        
        lastUpdate = millis();
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
    
    private void updatePositions() {
        if (lastUpdate == - 1) {
            return;
        }
        
        int deltaTime = millis() - lastUpdate;
        
        float thrust = ((1.261 * motorsRate[0]) - 0.339) * GRAVITY;
        if (thrust <= 0) {
            thrust = 0;
        }
        
        float gravity = MASS * GRAVITY;
        
        float accelerationY = (thrust - gravity) / MASS;
        float deltaTimeInSeconds = deltaTime * 0.001;
        
        position[1] += lastSpeed * deltaTimeInSeconds + (accelerationY * pow(deltaTimeInSeconds, 2)) / 2;
        
        if (position[1] <= 0) {
            position[1] = 0;
        }
        
        lastSpeed += accelerationY * deltaTimeInSeconds;
    }
}
