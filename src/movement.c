#include "movement.h"
#include "ports.h"

float wheel_rotation_to_meter(float rotation) {
	
	int R_to_M = tacho_get_count_per_m(MOTOR_LEFT, 0 );
	float Distance = rotation / R_to_M;
	return(Distance);
}

float meter_to_wheel_rotation(float length) 
{
	int R_to_M = tacho_get_count_per_m(MOTOR_LEFT, 0 );
	float Degree = length * R_to_M;
	return(Degree);
}

float rotate_robot(float degrees) {
}