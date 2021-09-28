#include "movement.h"
#include "ports.h"

float wheel_rotation_to_meter(float rotation) {
	/* TODO */
	int R_to_M = tacho_get_count_per_m(MOTOR_LEFT, 0 );

}

float meter_to_wheel_rotation(float length) {
	/* TODO */
	tacho_get_count_per_rot(, 0)
}

float rotate_robot(float degrees) {
	/* TODO */
}