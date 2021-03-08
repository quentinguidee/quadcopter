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
        
        enableSimModeButton = ui.addButton("enableSimMode")
           .setPosition(0, 0)
           .setSize(200, 26)
           .setCaptionLabel("Enable Sim Mode")
           .setGroup(sidebar);
        
        motorA = ui.addKnob("motorA")
           .setRange(1000, 2000)
           .setValue(1300)
           .setCaptionLabel("Motor A")
           .setPosition(15, 40)
           .setRadius(40)
           .setNumberOfTickMarks(10)
           .setTickMarkLength(1)
           .snapToTickMarks(false)
           .setColorForeground(0xfff2f2f2)
           .setColorBackground(0xff222222)
           .setDragDirection(Knob.ARC);
        
        motorB = ui.addKnob("motorB")
           .setRange(1000, 2000)
           .setValue(1300)
           .setCaptionLabel("Motor B")
           .setPosition(110, 40)
           .setWidth(1)
           .setRadius(40)
           .setNumberOfTickMarks(10)
           .setTickMarkLength(1)
           .snapToTickMarks(false)
           .setColorForeground(0xfff2f2f2)
           .setColorBackground(0xff222222)
           .setDragDirection(Knob.ARC);
        
        motorC = ui.addKnob("motorC")
           .setRange(1000, 2000)
           .setValue(1300)
           .setCaptionLabel("Motor C")
           .setPosition(15, 150)
           .setRadius(40)
           .setNumberOfTickMarks(10)
           .setTickMarkLength(1)
           .snapToTickMarks(false)
           .setColorForeground(0xfff2f2f2)
           .setColorBackground(0xff222222)
           .setDragDirection(Knob.ARC);
        
        motorD = ui.addKnob("motorD")
           .setRange(1000, 2000)
           .setValue(1300)
           .setCaptionLabel("Motor D")
           .setPosition(110, 150)
           .setWidth(1)
           .setRadius(40)
           .setNumberOfTickMarks(10)
           .setTickMarkLength(1)
           .snapToTickMarks(false)
           .setColorForeground(0xfff2f2f2)
           .setColorBackground(0xff222222)
           .setDragDirection(Knob.ARC);
    }
}

void enableSimMode() {
    drone.port.write("$S\n");
    println("[SENT————] $S");
    println("|||||||||| Trying to enable SimMode");
}
