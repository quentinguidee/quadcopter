import processing.serial.*;
import controlP5.*;


Drone drone;
UI ui;

void setup() {
    Serial port = new Serial(this, Serial.list()[3], 38400);
    drone = new Drone(port);
    
    // UI
    size(1600, 656, P3D);
    surface.setTitle("Quadcopter");
    surface.setResizable(true);
    
    ControlP5 p5 = new ControlP5(this);
    ui = new UI(p5);
}

void draw() {
    drone.tick();
}
