# Interface

Allows to communicate between the computer and the drone. The messages are horrible to read for humans, but it's to ensure the transfer speed.

## Input

### Movement

- X,Y,Z = Desired position
- R = Desired rotation

Format: `CXYZR`

### Commands

#### Drone

| Status | Format | Name                               |
| ------ | ------ | ---------------------------------- |
| DONE   | D0     | Turn off                           |
| DONE   | D1     | Turn on                            |
| DONE   | D2     | Lift off                           |
| TODO   | D3     | Land                               |
| DONE   | D4     | Start motors test (all, low speed) |
| DONE   | D5     | Stop motors test                   |

#### Wifi

| Status | Format | Name |
| ------ | ------ | ---- |
| DONE   | WP     | Ping |

#### Motors

| Status | Format | Name                        |
| ------ | ------ | --------------------------- |
| DONE   | M0X    | Turn off motor X            |
| DONE   | M1X    | Turn on motor X (low speed) |

### Simulator

| Status | Format | Name                   |
| ------ | ------ | ---------------------- |
| DONE   | S      | Enable simulation mode |

### Telemetry

| Status | Format | Name                     |
| ------ | ------ | ------------------------ |
| DONE   | T0     | Force set telemetry data |

### PID

| Status | Format | Name                                        |
| ------ | ------ | ------------------------------------------- |
| DONE   | PXYV   | Set the Y value of the PID X to the value V |
