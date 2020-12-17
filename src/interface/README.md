# Interface

Allows to communicate between the computer and the drone. The messages are horrible to read for humans, but it's to ensure the transfer speed.

## Input

### Movement

- X axis
- Y axis
- Z axis
- Rotation

Format: `x,y,z,r`

### Commands

#### Drone

| Status | Format | Name             |
| ------ | ------ | ---------------- |
| TODO   | D0     | Turn off         |
| TODO   | D1     | Turn on          |
| TODO   | D2     | Lift off         |
| TODO   | D2X    | Lift off of X cm |
| TODO   | D3     | Land             |

#### Motors

| Status | Format | Name                        |
| ------ | ------ | --------------------------- |
| TODO   | M0X    | Turn off motor X            |
| TODO   | M1X    | Turn on motor X (low speed) |

#### Motors LED

| Status | Format | Name                   |
| ------ | ------ | ---------------------- |
| TODO   | L0X    | Turn off motor X's LED |
| TODO   | L1X    | Turn on motor X's LED  |

#### Piezo

| Status | Format | Name           |
| ------ | ------ | -------------- |
| TODO   | P0     | Turn off piezo |
| TODO   | P1     | Turn on piezo  |
