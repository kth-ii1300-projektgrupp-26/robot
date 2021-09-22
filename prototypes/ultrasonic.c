/*
 * Fil för att testa "Ultrasonic Sensor".
 * Skapad av Hannes Mann 2021-09-22.
 */

#include "brick.h"
#include <stdio.h>

#define SENSOR_ULTRASONIC IN4

int main() {
	if(!brick_init()) {
		printf("Fel uppstod i brick_init().\n");
		return 1;
	}

	if(sensor_is_plugged(SENSOR_ULTRASONIC, SENSOR_TYPE__NONE_)) {
		POOL_T sensor = sensor_search(LEGO_EV3_US);

		/* Sätter läget på ultrasonic sensorn till att mäta kontinuerligt i centimeter. */
		us_set_mode_us_dist_cm(sensor);
		/* Ultrasonic sensorn lägger in längden från en vägg i value0. */
		float distance = sensor_get_value0(sensor, 0);

		printf("Distans till vägg: %f\n", distance);
	}
	else {
		printf("Ultrasonic sensor not plugged in.\n");
	}

	brick_uninit();
	return 0;
}