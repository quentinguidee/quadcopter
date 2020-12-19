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

/**
 * Status LED (blue component)
 */
constexpr uint8_t STATUS_LED_RED_PIN = 8;

/**
 * Status LED (red component)
 */
constexpr uint8_t STATUS_LED_BLUE_PIN = 7;

/**
 * Status LED (green component)
 */
constexpr uint8_t STATUS_LED_GREEN_PIN = 6;

///////////////////
// === PIEZO === //
///////////////////

/**
 * Piezo Pin
 * Pin type: D
 */
constexpr uint8_t PIEZO_PIN = 53;

/**
 * Number of frequencies for the startup ring.
 */
constexpr uint8_t STARTUP_FREQUENCIES_COUNT = 5;

/**
 * Frequencies for the startup ring.
 */
constexpr int STARTUP_FREQUENCIES[STARTUP_FREQUENCIES_COUNT] = {523, 887, 887, 523, 1046};

////////////////////
// === BUTTON === //
////////////////////

constexpr uint8_t POWER_TOGGLE_BUTTON_PIN = 52;

#endif /* SETTINGS_H */
