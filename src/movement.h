#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "brick.h"

/*
 * "Direction type".
 *
 * Väljer om roboten behöver åka till vänster eller höger relativt väggen
 * som den har framför sig i början.
 */
typedef enum {
	DIRECTION_LEFT,
	DIRECTION_RIGHT
} direction_t;

/*
 * EV3 motorer mäter "position" genom rotation av hjulen. När den har roterat
 * 360 grader så har roboten alltså rört sig en längd som är lika med omkretsen
 * på hjulen.
 *
 * Referens: https://ev3lessons.com/en/Resources/WheelConverter/
 */
#define WHEEL_CIRCUMFERENCE_METER (17.59292 / 100.0)

/* .rotationern på hjulen till längden som roboten har åkt. */
float wheel_rotation_to_meter(float rotation);

/* Gör om längden som roboten har åkt till rotationer på hjulen. */
float meter_to_wheel_rotation(float length);

/*
 * Funktion som tar in avstånd och hastighet och rör på robotten.
 * distance får vara negativt men speed måste alltid vara mellan 0-1 (0% till 100%).
 */
void move( float distance, float speed);

/*
 * "Motor position type".
 *
 * En struktur med värden för både vänstra och högra hjulet.
 */
typedef struct {
	int left;
	int right;
} motor_position_t;

/* Hur snabbt roboten ska rotera. */
#define ROTATION_SPEED 0.05

/*
 * Roterar roboten med x antal grader. Minustecken betyder vänster och
 * plustecken betyder höger.
 *
 * Funktionen returnerar skillnad i vänster och höger motors position.
 */
motor_position_t rotate_robot(float degrees);

#endif