#ifndef PORTS_H
#define PORTS_H

#include "brick.h"

#define MOTOR_LEFT OUTB
#define MOTOR_RIGHT OUTC
#define MOTOR_MEDIUM OUTA /*OUTA A KAN ÄNDRAS SEN*/

#define MOTOR_BOTH (MOTOR_LEFT | MOTOR_RIGHT)

#define SENSOR_GYRO IN2
#define SENSOR_ULTRASONIC IN3

#endif