# Interface

Allows to communicate between the computer and the drone. The messages are horrible to read for humans, but it's to ensure the transfer speed.

## Input

### Movement

- X axis (0 to 99)
- Y axis (0 to 99)
- Z axis (0 to 99)
- Rotation (0 to 99)

Format: `CXXYYZZRR`

### Commands

#### Drone

| Status | Format | Name             |
| ------ | ------ | ---------------- |
| DONE   | D0     | Turn off         |
| DONE   | D1     | Turn on          |
| TODO   | D2     | Lift off         |
| TODO   | D2X    | Lift off of X cm |
| TODO   | D3     | Land             |

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
