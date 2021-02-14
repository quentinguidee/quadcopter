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
| TODO   | D0     | Turn off         |
| TODO   | D1     | Turn on          |
| TODO   | D2     | Lift off         |
| TODO   | D2X    | Lift off of X cm |
| TODO   | D3     | Land             |

#### Wifi

| Status | Format | Name |
| ------ | ------ | ---- |
| TODO   | WP     | Ping |
| TODO   | WP     | Ping |

#### Motors

| Status | Format | Name                        |
| ------ | ------ | --------------------------- |
| TODO   | M0X    | Turn off motor X            |
| TODO   | M1X    | Turn on motor X (low speed) |
