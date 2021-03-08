public class UI {
    ControlP5 ui;
    
    public UI(ControlP5 ui) {
        this.ui = ui;
        setup();
    }
    
    private void setup() {
        Group sidebar = ui.addGroup("sidebar")
           .setPosition(0, 0)
           .setColorBackground(0xff111111);
        
        enableSimModeButton = ui.addButton("enableSimMode")
           .setPosition(0, 0)
           .setSize(200, 26)
           .setCaptionLabel("Enable Sim Mode")
           .setGroup(sidebar); 
    }
}

void enableSimMode() {
    drone.port.write("$S\n");
    println("[SENT————] $S");
    println("|||||||||| Trying to enable SimMode");
}
