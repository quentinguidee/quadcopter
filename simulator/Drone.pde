import processing.serial.*;

public class Drone {
    Serial port;
    String buffer;
    
    boolean isOn = false;
    
    boolean[] ledsState = { false, false, false, false };
    float[] motorsRate = { 0 ,0, 0, 0 }; // Between 0 and 1
    float[] position = { 0, 0, 0 }; // left-right/up-down/front-back
    float[] angles = { 0, 0, 0 }; // In rad
    float[] lastSpeed = { 0, 0, 0 };
    float[] lastSpeedMotors = { 0, 0, 0, 0 };
    float[] drawedPosition = { 0, 0, 0 };
    final int[][] LEDS_POSITIONS = { { - 25, - 25 } , { 25, - 25 } , { - 25, 25 } , { 25, 25 } };
    
    final int RED = 0xffff0000;
    final int BLUE = 0xff0000ff;
    
    int lastUpdate = - 1;
    
    final float MASS = 2.0; // in kg
    final float GRAVITY = 9.81; // in m/s^2
    final float LENGTH_CENTER_TO_MOTOR = 0.35; // in m
    
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
        translate(width / 2 - drawedPosition[0], height - 100 - drawedPosition[1], 0 - drawedPosition[2] - 100);

        rotateX(angles[0]);
        rotateY(angles[1]);
        rotateZ(angles[2]);

        stroke(0xff888888);
        noFill();
        box(50, 2, 50);
        drawLEDs();
        
        popMatrix();
    }
    
    private void drawLEDs() {
        for (int i = 0; i < 4; ++i) {
            if (ledsState[i]) {
                int[] ledPosition = LEDS_POSITIONS[i];
                translate(ledPosition[0], 0, ledPosition[1]);
                pushMatrix();
                noStroke();
                fill(i <= 1 ? BLUE : RED);
                box(4, 4, 4);
                popMatrix();
                translate(-ledPosition[0], 0, -ledPosition[1]);
            }
        }
    }
    
    private void updatePositions() {
        if (lastUpdate == - 1) {
            return;
        }
        
        int deltaTime = millis() - lastUpdate;
        
        float[] thrustMotors = {0, 0, 0, 0};
        float thrustTotal = 0;
        for (int i = 0; i < 4; ++i) {
            float thrust = ((1.261 * (motorsRate[i] - random(0, 0.02 * i))) - 0.339) * GRAVITY;
            if (thrust <= 0) {
                thrust = 0;
            }
            thrustMotors[i] = thrust;
            thrustTotal += thrust;

            lastSpeedMotors[i] = thrust / MASS;
        }
        
        float gravity = MASS * GRAVITY;
        
        float accelerationNormal = thrustTotal / MASS;
        int[] accelerationsCoeff = { 1, 1, 1 };
        if (angles[0] < 0) { accelerationsCoeff[0] = -1; }
        if (angles[2] < 0) { accelerationsCoeff[2] = -1; }
        float[] accelerations = {
            accelerationNormal * sin(angles[0]) * cos(angles[2]) * accelerationsCoeff[0],
            accelerationNormal * cos(angles[0]) * cos(angles[2]) - (gravity / MASS),
            accelerationNormal * cos(angles[0]) * sin(angles[2]) * accelerationsCoeff[2]
        };

        float deltaTimeInSeconds = deltaTime * 0.001;

        int[][] coeff = { { - 1, - 1 } , { 1, - 1 } , { - 1, 1 } , { 1, 1 } };
        for (int i = 0; i < 4; ++i) {
            angles[0] += coeff[i][0] * (lastSpeedMotors[i] * pow(deltaTimeInSeconds, 2)) / LENGTH_CENTER_TO_MOTOR;
            angles[2] += coeff[i][1] * (lastSpeedMotors[i] * pow(deltaTimeInSeconds, 2)) / LENGTH_CENTER_TO_MOTOR;
        }
        
        for (int i = 0; i < 3; ++i) {
            position[i] += lastSpeed[i] * deltaTimeInSeconds + (accelerations[i] * pow(deltaTimeInSeconds, 2)) / 2;
        }
        
        if (position[1] <= 0) {
            for (int i = 0; i < 3; ++i) {
                position[i] = 0;
                lastSpeed[i] = 0;
                angles[i] = 0;
            }
        } else {
            for (int i = 0; i < 3; ++i) {
                lastSpeed[i] += accelerations[i] * deltaTimeInSeconds;
            }
        }
    }
}
