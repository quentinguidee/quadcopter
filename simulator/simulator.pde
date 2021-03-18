import processing.serial.*;
import controlP5.*;


Drone drone;
UI ui;

void setup() {
    drone = new Drone();

    // UI
    size(1600, 656, P3D);
    background(0xff111111);
    surface.setTitle("Quadcopter");
    surface.setResizable(true);
    
    ControlP5 p5 = new ControlP5(this);
    ui = new UI(p5);
}

void draw() {
    drone.tick();
}
