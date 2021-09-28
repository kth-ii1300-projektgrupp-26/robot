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
 * TODO: kan tacho_get_count_per_m göra det här?
 */
#define WHEEL_CIRCUMFERENCE_METER 0

/* Gör om rotationern på hjulen till längden som roboten har åkt. */
float wheel_rotation_to_meter(float rotation);

/* Gör om längden som roboten har åkt till rotationer på hjulen. */
float meter_to_wheel_rotation(float length);

/*
 * "Motor position type".
 *
 * En struktur med värden för både vänstra och högra hjulet.
 */
typedef struct {
	int left;
	int right;
} motor_position_t;

/*
 * Roterar roboten med x antal grader. Minustecken betyder vänster och
 * plustecken betyder höger.
 *
 * Funktionen returnerar skillnad i vänster och höger motors position.
 */
motor_position_t rotate_robot(float degrees);

#endif