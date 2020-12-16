#ifndef SETTINGS_H
#define SETTINGS_H

/**
 * ESC Motor A Pin (front left)
 */
constexpr uint8_t ESC_MOTOR_A_PIN = 6;

/**
 * ESC Motor B Pin (front right)
 */
constexpr uint8_t ESC_MOTOR_B_PIN = 5;

/**
 * ESC Motor C Pin (rear left)
 */
constexpr uint8_t ESC_MOTOR_C_PIN = 10;

/**
 * ESC Motor D Pin (rear right)
 */
constexpr uint8_t ESC_MOTOR_D_PIN = 11;

/**
 * LED Motor A Pin (front left)
 */
constexpr uint8_t LED_MOTOR_A_PIN = 2;

/**
 * LED Motor B Pin (front right)
 */
constexpr uint8_t LED_MOTOR_B_PIN = 7;

/**
 * LED Motor C Pin (rear left)
 */
constexpr uint8_t LED_MOTOR_C_PIN = 8;

/**
 * LED Motor D Pin (rear right)
 */
constexpr uint8_t LED_MOTOR_D_PIN = 12;

/**
 * Pulse width corresponding to 0°
 */
constexpr int16_t MIN_ESC_PULSE_WIDTH = 1000;

/**
 * Pulse width corresponding to 180°
 */
constexpr int32_t MAX_ESC_PULSE_WIDTH = 2000;

#endif /* SETTINGS_H */
