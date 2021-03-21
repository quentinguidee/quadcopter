import processing.serial.*;

public class Drone {
    Serial port;
    String buffer;
    
    boolean isInSimMode = false;
    boolean isOn = false;
    boolean draw = true;
    public boolean enableManualMove = false;
    
    Led[] leds = {
        new Led(-25, -25, Color.BLUE),
        new Led( 25, -25, Color.BLUE),
        new Led(-25,  25, Color.RED),
        new Led( 25,  25, Color.RED)
    };

    float[] position = { 0, 0, 0 }; // left-right/up-down/front-back
    float[] angles = { 0, 0, 0 }; // In rad

    float[] accelerations = { 0, 0, 0 }; // In m/s^2
    float[] anglesRate = { 0, 0, 0 }; // In rad/s

    float[] motorsRate = { 0 ,0, 0, 0 }; // Between 0 and 1
    float[] lastSpeed = { 0, 0, 0 };
    float[] lastSpeedMotors = { 0, 0, 0, 0 };

    float[] drawedPosition = { 0, 0, 0 };

    int[][] MOTORS_COEFF = { { - 1, - 1 } , { 1, - 1 } , { - 1, 1 } , { 1, 1 } };

    float deltaTime = -1;

    final float MASS = 2.0; // in kg
    final float GRAVITY = 9.81; // in m/s^2
    final float LENGTH_CENTER_TO_MOTOR = 0.35; // in m

    public Drone() {}

    public void serialConnect(PApplet applet) {
        this.port = new Serial(applet, Serial.list()[3], 38400);
    }

    public Serial getPort() {
        return port;
    }

    public boolean isOn() {
        return isOn;
    }

    public boolean isInSimMode() {
        return isInSimMode;
    }

    public void tick() {
        if (port == null) return;

        readSerial();
        if (draw) {
            println("draw at " + position[0] + " " + position[1] + " " + position[2]);
            draw();
            draw = false;
        }
    }

    private void readSerial() {
        int reads = 0;
        int MAX_READS = 10;
        while (port.available() > 0) {
            char character = port.readChar();
            if (character == '\n' && buffer != "") {
                println(buffer);
                if (buffer.charAt(0) == '#') {
                    onCommandReceived(buffer);
                    reads++;
                }
                buffer = "";
                if (reads >= MAX_READS) return;
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
            boolean enable = boolean(Integer.parseInt(str(buffer.charAt(3))));
            println("|||||||||| LED " + led + " set to " + enable);
            if (enable) {
                leds[led].on();
            } else {
                leds[led].off();
            }
            draw = true;
        } else if (category == 'M') {
            if (buffer.charAt(2) == 'S') {
                String s = buffer.substring(3, buffer.length());
                String[] speeds = split(s, ',');
                if (speeds.length == 5) {
                    for (int i = 0; i < 4; ++i) {
                        float value = Float.valueOf(speeds[i]);
                        motorsRate[i] = value / 180.0;
                        ui.getMotorView(i).setValue(value);
                    }
                    deltaTime = Float.valueOf(speeds[4]);
                }
                updatePositions();
                draw = true;
            }
        }
    }

    private void simModeEnabledCallback() {
        isInSimMode = true;
    }

    private void draw() {
        for (int i = 0; i < 3; ++i) {
            drawedPosition[i] = position[i] * 40;
        }

        background(0xff111111);

        pushMatrix();
        translate(width / 2, height - 100, -100);
        stroke(0xff888888);
        noFill();
        box(500, 0, 500);
        translate(-drawedPosition[0], -drawedPosition[1], -drawedPosition[2]);

        rotateX(-angles[0]);
        rotateY(-angles[1]);
        rotateZ(angles[2]);

        box(50, 2, 50);
        drawLEDs();

        popMatrix();
    }

    private void drawLEDs() {
        for (int i = 0; i < 4; ++i) {
            leds[i].draw();
        }
    }

    private void sendTelemetry() {
        println("[SEND----] $T0" + position[1] + "," + accelerations[0] + "," + accelerations[2] + "," + accelerations[1] + "," + anglesRate[0] + "," + anglesRate[2] + "," + anglesRate[1] + "\n");
        port.write("$T0" + position[1] + "," + accelerations[0] + "," + accelerations[2] + "," + accelerations[1] + "," + anglesRate[0] + "," + anglesRate[2] + "," + anglesRate[1] + "\n");
    }

    private void moveToDesiredPosition() {
        if (!enableManualMove) { return; }

        enableManualMove = false;

        println("[SEND----] $C"
            + (ui.getMovementXYSlider().getArrayValue()[0] - 50) + ","
            + (ui.getMovementXYSlider().getArrayValue()[1] - 50) + ","
            + (ui.getMovementZRSlider().getArrayValue()[1] - 50) + ","
            + (ui.getMovementZRSlider().getArrayValue()[0] - 50));

        port.write("$C"
            + (ui.getMovementXYSlider().getArrayValue()[0] - 50) + ","
            + (ui.getMovementXYSlider().getArrayValue()[1] - 50) + ","
            + (ui.getMovementZRSlider().getArrayValue()[1] - 50) + ","
            + (ui.getMovementZRSlider().getArrayValue()[0] - 50) + "\n");
    }

    private void updatePositions() {
        if (deltaTime == -1) return;

        float[] thrustMotors = {0, 0, 0, 0};
        float thrustTotal = 0;
        for (int i = 0; i < 4; ++i) {
            float thrust = ((1.261 * (motorsRate[i]/* -random(0, 0.01 * i) */)) - 0.339) * GRAVITY;
            if (thrust <= 0) thrust = 0;
            thrustMotors[i] = thrust;
            thrustTotal += thrust;

            lastSpeedMotors[i] = thrust / MASS;
        }

        float accelerationNormal = thrustTotal / MASS;
        int[] accelerationsCoeff = { 1, 1, 1 };

        if (angles[0] < 0) { accelerationsCoeff[0] = -1; }
        if (angles[2] < 0) { accelerationsCoeff[2] = -1; }

        accelerations[0] = accelerationNormal * sin(angles[0]) * cos(angles[2]) * accelerationsCoeff[0];
        accelerations[1] = accelerationNormal * cos(angles[0]) * cos(angles[2]) - GRAVITY;
        accelerations[2] = accelerationNormal * cos(angles[0]) * sin(angles[2]) * accelerationsCoeff[2];

        float deltaTimeInSeconds = deltaTime * 0.001;

        for (int i = 0; i < 4; ++i) {
            float a = lastSpeedMotors[i] / LENGTH_CENTER_TO_MOTOR;

            // ß = (v/r)*t
            angles[0] += MOTORS_COEFF[i][0] * a * deltaTimeInSeconds;
            angles[2] += MOTORS_COEFF[i][1] * a * deltaTimeInSeconds;

            // ω = v/r
            anglesRate[0] += MOTORS_COEFF[i][0] * a;
            anglesRate[2] += MOTORS_COEFF[i][1] * a;
        }

        for (int i = 0; i < 3; ++i) {
            position[i] += lastSpeed[i] * deltaTimeInSeconds + (accelerations[i] * pow(deltaTimeInSeconds, 2)) / 2;
        }

        if (position[1] <= 0) {
            for (int i = 0; i < 3; ++i) {
                position[i] = 0;
                accelerations[i] = 0;
                anglesRate[i] = 0;
                lastSpeed[i] = 0;
                angles[i] = 0;
            }
            accelerations[1] = -9.81;
        } else {
            for (int i = 0; i < 3; ++i) {
                lastSpeed[i] += accelerations[i] * deltaTimeInSeconds;
            }
        }

        sendTelemetry();
        moveToDesiredPosition();
    }
}
