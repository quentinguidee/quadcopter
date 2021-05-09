#ifndef SETTINGS_H
#define SETTINGS_H

namespace Settings {

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
constexpr uint8_t LED_MOTOR_A_PIN = 48;

/**
 * LED Motor B Pin (front right)
 * Pin type: D
 */
constexpr uint8_t LED_MOTOR_B_PIN = 49;

/**
 * LED Motor C Pin (rear left)
 * Pin type: D
 */
constexpr uint8_t LED_MOTOR_C_PIN = 42;

/**
 * LED Motor D Pin (rear right)
 * Pin type: D
 */
constexpr uint8_t LED_MOTOR_D_PIN = 43;

/**
 * LED Simulator mode Pin
 * Pin type: D
 */
constexpr uint8_t LED_SIMULATOR_PIN = 51;

////////////////////
// === BUTTON === //
////////////////////

/**
 * Toggle button pin (turns on/off the drone)
 * Pin type: D
 */
constexpr uint8_t POWER_TOGGLE_BUTTON_PIN = 52;

}  // namespace Settings

#endif /* SETTINGS_H */
