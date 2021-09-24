/*
 * Den här filen definerar fakta om roboten, som vart motorer/sensorer sitter
 * och dimensionerna på roboten.
 */

#include "brick.h"

#define MOTOR_LEFT OUTB
#define MOTOR_RIGHT OUTC

#define MOTOR_BOTH (MOTOR_LEFT | MOTOR_RIGHT)

#define SENSOR_GYRO IN2
#define SENSOR_ULTRASONIC IN3

/* TODO: Bredd på robot */
#define ROBOT_WIDTH_CM 0
/* TODO: Längd på robot */
#define ROBOT_LENGTH_CM 0