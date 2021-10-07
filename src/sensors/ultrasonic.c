#include "sensors/ultrasonic.h"
#include "ports.h"

bool can_find_object() {
	float distance = sensor_get_value0(SENSOR_ULTRASONIC, 0) / 1000;

	return distance > 0.05 && distance < 2.50;
}

float get_distance_to_object() {
	float distance = sensor_get_value0(SENSOR_ULTRASONIC, 0) / 1000;
	return distance;
}