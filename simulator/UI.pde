public class UI {
    ControlP5 ui;
    
    Knob motorA, motorB, motorC, motorD;
    
    public UI(ControlP5 ui) {
        this.ui = ui;
        draw();
    }
    
    private void draw() {
        drawSidebar();
    }
    
    private void drawSidebar() {
        Group sidebar = ui.addGroup("sidebar")
           .setPosition(0, 0)
           .setColorBackground(0xff111111);

        ui.addButton("serialConnect")
           .setPosition(0, 0)
           .setSize(200, 26)
           .setCaptionLabel("Serial Connect")
           .setGroup(sidebar);
        
        ui.addButton("enableSimMode")
           .setPosition(0, 27)
           .setSize(200, 26)
           .setCaptionLabel("Enable Sim Mode")
           .setGroup(sidebar);

        ui.addButton("toggleDrone")
           .setPosition(0, 54)
           .setSize(200, 26)
           .setCaptionLabel("On/Off")
           .setGroup(sidebar);
        
        motorA = ui.addKnob("motorA")
           .setRange(0, 180)
           .setValue(0)
           .setCaptionLabel("Motor A")
           .setPosition(15, 93)
           .setRadius(40)
           .setNumberOfTickMarks(10)
           .setTickMarkLength(1)
           .snapToTickMarks(false)
           .setColorForeground(0xfff2f2f2)
           .setColorBackground(0xff222222)
           .setDragDirection(Knob.ARC);
        
        motorB = ui.addKnob("motorB")
           .setRange(0, 180)
           .setValue(0)
           .setCaptionLabel("Motor B")
           .setPosition(110, 93)
           .setWidth(1)
           .setRadius(40)
           .setNumberOfTickMarks(10)
           .setTickMarkLength(1)
           .snapToTickMarks(false)
           .setColorForeground(0xfff2f2f2)
           .setColorBackground(0xff222222)
           .setDragDirection(Knob.ARC);
        
        motorC = ui.addKnob("motorC")
           .setRange(0, 180)
           .setValue(0)
           .setCaptionLabel("Motor C")
           .setPosition(15, 203)
           .setRadius(40)
           .setNumberOfTickMarks(10)
           .setTickMarkLength(1)
           .snapToTickMarks(false)
           .setColorForeground(0xfff2f2f2)
           .setColorBackground(0xff222222)
           .setDragDirection(Knob.ARC);
        
        motorD = ui.addKnob("motorD")
           .setRange(0, 180)
           .setValue(0)
           .setCaptionLabel("Motor D")
           .setPosition(110, 203)
           .setWidth(1)
           .setRadius(40)
           .setNumberOfTickMarks(10)
           .setTickMarkLength(1)
           .snapToTickMarks(false)
           .setColorForeground(0xfff2f2f2)
           .setColorBackground(0xff222222)
           .setDragDirection(Knob.ARC);

        Group pidTuning = ui.addGroup("pidTuning")
           .setPosition(0, 310)
           .setColorBackground(0xff111111)
           .setGroup(sidebar)
           .hideBar();
        
        String[] pids = {
            "PID Angle X",
            "PID Angle Y",
            "PID Angle Z",
            "PID Altitude",
            "PID Angle Rate X",
            "PID Angle Rate Y",
            "PID Angle Rate Z",
            "PID Altitude Rate",
        };

        for (int i = 0; i < 8; ++i) {
            ui.addTextfield("pid" + i + "kp")
            .setCaptionLabel(pids[i] + " (KP)")
            .setPosition(20, i * 40)
            .setSize(100, 20)
            .setGroup(pidTuning);

            ui.addTextfield("pid" + i + "ki")
            .setCaptionLabel(pids[i] + " (KI)")
            .setPosition(140, i * 40)
            .setSize(100, 20)
            .setGroup(pidTuning);

            ui.addTextfield("pid" + i + "kd")
            .setCaptionLabel(pids[i] + " (KD)")
            .setPosition(260, i * 40)
            .setSize(100, 20)
            .setGroup(pidTuning);
        }
    }

    public Knob getMotorView(int motorID) {
        switch (motorID) {
            case 0: return motorA;
            case 1: return motorB;
            case 2: return motorC;
            case 3: return motorD;
        }
        return null;
    }

    public Knob getMotorAView() { return motorA; }
    public Knob getMotorBView() { return motorB; }
    public Knob getMotorCView() { return motorC; }
    public Knob getMotorDView() { return motorD; }
}

void enableSimMode() {
    drone.getPort().write("$S\n");
    println("[SENT————] $S");
    println("|||||||||| Trying to enable SimMode");
}

void toggleDrone() {
    if (drone.isOn()) {
        drone.getPort().write("$D0\n");
        println("[SENT————] $D0");
        println("|||||||||| Shutdown");
        drone.isOn = false;
    } else {
        drone.getPort().write("$D1\n");
        println("[SENT————] $D1");
        println("|||||||||| Startup");
        drone.isOn = true;
    }
}

void serialConnect() { drone.serialConnect(this); }

void pid0kp(String value) { drone.getPort().write("$P0P" + value + "\n"); }
void pid0ki(String value) { drone.getPort().write("$P0I" + value + "\n"); }
void pid0kd(String value) { drone.getPort().write("$P0D" + value + "\n"); }

void pid1kp(String value) { drone.getPort().write("$P1P" + value + "\n"); }
void pid1ki(String value) { drone.getPort().write("$P1I" + value + "\n"); }
void pid1kd(String value) { drone.getPort().write("$P1D" + value + "\n"); }

void pid2kp(String value) { drone.getPort().write("$P2P" + value + "\n"); }
void pid2ki(String value) { drone.getPort().write("$P2I" + value + "\n"); }
void pid2kd(String value) { drone.getPort().write("$P2D" + value + "\n"); }

void pid3kp(String value) { drone.getPort().write("$P3P" + value + "\n"); }
void pid3ki(String value) { drone.getPort().write("$P3I" + value + "\n"); }
void pid3kd(String value) { drone.getPort().write("$P3D" + value + "\n"); }

void pid4kp(String value) { drone.getPort().write("$P4P" + value + "\n"); }
void pid4ki(String value) { drone.getPort().write("$P4I" + value + "\n"); }
void pid4kd(String value) { drone.getPort().write("$P4D" + value + "\n"); }

void pid5kp(String value) { drone.getPort().write("$P5P" + value + "\n"); }
void pid5ki(String value) { drone.getPort().write("$P5I" + value + "\n"); }
void pid5kd(String value) { drone.getPort().write("$P5D" + value + "\n"); }

void pid6kp(String value) { drone.getPort().write("$P6P" + value + "\n"); }
void pid6ki(String value) { drone.getPort().write("$P6I" + value + "\n"); }
void pid6kd(String value) { drone.getPort().write("$P6D" + value + "\n"); }

void pid7kp(String value) { drone.getPort().write("$P7P" + value + "\n"); }
void pid7ki(String value) { drone.getPort().write("$P7I" + value + "\n"); }
void pid7kd(String value) { drone.getPort().write("$P7D" + value + "\n"); }
