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
