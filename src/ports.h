#include "brick.h"

#define MOTOR_LEFT OUTB
#define MOTOR_RIGHT OUTC

#define MOTOR_BOTH (MOTOR_LEFT | MOTOR_RIGHT)

#define SENSOR_GYRO IN2
#define SENSOR_ULTRASONIC IN3