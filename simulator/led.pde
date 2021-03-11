public class Led {
    boolean on = false;
    
    int[] position;
    int hex;

    public Led(int[] position) {
        this.position = position;
    }

    public Led(int x, int z, int hex) {
        this.position = new int[] { x, z };
        this.hex = hex;
    }

    public void draw() {
        if (on) {
            translate(position[0], 0, position[1]);
            pushMatrix();
            noStroke();
            fill(hex);
            box(4, 4, 4);
            popMatrix();
            translate(-position[0], 0, -position[1]);
        }
    }

    public void on() { on = true; }
    public void off() { on = false; }
}
