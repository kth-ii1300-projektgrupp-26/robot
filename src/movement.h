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

/* .rotationern på hjulen till längden som roboten har åkt. */
float wheel_rotation_to_meter(float rotation);

/* Gör om längden som roboten har åkt till rotationer på hjulen. */
float meter_to_wheel_rotation(float length);

/*
 * Roterar roboten med x antal grader. Minustecken betyder vänster och
 * plustecken betyder höger.
 *
 * Funktionen returnerar skillnad i vänster och höger motors position.
 */
float rotate_robot(float degrees); /* TODO: kommer skillnaden på båda motorer att vara exakt samma? */

#endif