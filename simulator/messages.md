# Messages

Allows to communicate between the Arduino and the simulator.

## Format

### Input (#)

| Format | Name                        |
| ------ | --------------------------- |
| SC     | Simulation enabled callback |
| LX0    | Turn off LED X.             |
| LX1    | Turn on LED X.              |

### Output ($)

| Format | Name             |
| ------ | ---------------- |
| S      | Enabled sim mode |
