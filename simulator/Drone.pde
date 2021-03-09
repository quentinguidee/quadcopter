import processing.serial.*;

public class Drone {
    Serial port;
    String buffer;
    
    boolean isOn = false;
    
    boolean[] ledsState = { false, false, false, false };
    float[] motorsRate = { 0 ,0, 0, 0 }; // Between 0 and 1
    float[] position = { 0, 0, 0 }; // left-right/up-down/front-back
    float[] drawedPosition = { 0, 0, 0 };
    final int[][] LEDS_POSITIONS = { { - 25, - 25 } , { 25, - 25 } , { - 25, 25 } , { 25, 25 } };
    
    final int RED = 0xffff0000;
    final int BLUE = 0xff0000ff;
    
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
        lastUpdate = millis();
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
        //println("[RECEIVED] " + buffer);
        char category = buffer.charAt(1);
        if (category == 'S') {
            simModeEnabledCallback();
            println("|||||||||| SimMode enabled");
        } else if (category == 'L') {
            int led = Integer.parseInt(str(buffer.charAt(2)));
            boolean action = boolean(Integer.parseInt(str(buffer.charAt(3))));
            println("|||||||||| LED " + led + " set to " + action);
            ledsState[led] = action;
        } else if (category == 'M') {
            if (buffer.charAt(2) == 'S') {
                println(buffer);
                int motorID = Integer.valueOf(str(buffer.charAt(3)));
                motorsRate[motorID] = Float.valueOf(buffer.substring(4, buffer.length() - 1)) / 180.0;
            }
        }
    }
    
    private void simModeEnabledCallback() {
        enableSimModeButton.setColorBackground(0xff222222);
        enableSimModeButton.setColorActive(0xff222222);
        isOn = true;
    }
    
    private void draw() {
        updatePositions();
        
        for (int i = 0; i < 3; ++i) {
            drawedPosition[i] = position[i] * 40;
        }
        
        background(0xff111111);
        
        pushMatrix();
        translate(width / 2 - drawedPosition[0], height - 100 - drawedPosition[1], 0 - drawedPosition[2]);
        rotateY(0);
        stroke(0xff888888);
        noFill();
        box(50, 2, 50);
        popMatrix();
        
        drawLEDs();
    }
    
    private void drawLEDs() {
        for (int i = 0; i < 4; ++i) {
            if (ledsState[i]) {
                int[] ledPosition = LEDS_POSITIONS[i];
                pushMatrix();
                translate(width / 2 + ledPosition[0] - drawedPosition[0], height - 100 - drawedPosition[1], 0 + ledPosition[1] - drawedPosition[2]);
                rotateY(0);
                noStroke();
                fill(i <= 1 ? BLUE : RED);
                box(4, 4, 4);
                popMatrix();
            }
        }
    }
    
    private void updatePositions() {
        if (lastUpdate == - 1) {
            return;
        }
        
        int deltaTime = millis() - lastUpdate;
        
        float[] thrustMotors = {0, 0, 0, 0};
        float thrustY = 0;
        for (int i = 0; i < 4; ++i) {
            println(i + " " + motorsRate[i]);
            float thrust = ((1.261 * motorsRate[i]) - 0.339) * GRAVITY;
            if (thrust <= 0) {
                thrust = 0;
            }
            thrustMotors[i] = thrust;
            thrustY += thrust;
            println(i + " " + thrustMotors[i]);
        }
        
        float gravity = MASS * GRAVITY;
        
        float accelerationY = (thrustY - gravity) / MASS;
        println(accelerationY);
        float deltaTimeInSeconds = deltaTime * 0.001;
        
        position[1] += lastSpeed * deltaTimeInSeconds + (accelerationY * pow(deltaTimeInSeconds, 2)) / 2;
        
        if (position[1] <= 0) {
            position[1] = 0;
            lastSpeed = 0;
        } else {
            lastSpeed += accelerationY * deltaTimeInSeconds;
        }
        
    }
}
