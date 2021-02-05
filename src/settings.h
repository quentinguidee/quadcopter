#ifndef SETTINGS_H
#define SETTINGS_H

/////////////////
// === ESC === //
/////////////////

/**
 * ESC Motor A Pin (front left)
 * Pin type: D~
 */
constexpr uint8_t ESC_MOTOR_A_PIN = 2;

/**
 * ESC Motor B Pin (front right)
 * Pin type: D~
 */
constexpr uint8_t ESC_MOTOR_B_PIN = 3;

/**
 * ESC Motor C Pin (rear left)
 * Pin type: D~
 */
constexpr uint8_t ESC_MOTOR_C_PIN = 4;

/**
 * ESC Motor D Pin (rear right)
 * Pin type: D~
 */
constexpr uint8_t ESC_MOTOR_D_PIN = 5;

/**
 * Pulse width corresponding to 0°
 */
constexpr int16_t MIN_ESC_PULSE_WIDTH = 1000;

/**
 * Pulse width corresponding to 180°
 */
constexpr int16_t MAX_ESC_PULSE_WIDTH = 2000;

/////////////////
// === LED === //
/////////////////

/**
 * LED Motor A Pin (front left)
 * Pin type: D
 */
constexpr uint8_t LED_MOTOR_A_PIN = 22;

/**
 * LED Motor B Pin (front right)
 * Pin type: D
 */
constexpr uint8_t LED_MOTOR_B_PIN = 23;

/**
 * LED Motor C Pin (rear left)
 * Pin type: D
 */
constexpr uint8_t LED_MOTOR_C_PIN = 24;

/**
 * LED Motor D Pin (rear right)
 * Pin type: D
 */
constexpr uint8_t LED_MOTOR_D_PIN = 25;

////////////////////
// === BUTTON === //
////////////////////

/**
 * Toggle button pin (turns on/off the drone)
 * Pin type: D
 */
constexpr uint8_t POWER_TOGGLE_BUTTON_PIN = 52;

///////////////////////
// === JEWEL LED === //
///////////////////////

/**
 * Jewel LED Pin
 * Pin type: D~
 */
constexpr uint8_t JEWEL_LED_PIN = 8;

#endif /* SETTINGS_H */
