/*
 * Fil för att testa "Gyro Sensor".
 * Skapad av Hannes Mann 2021-09-22.
 */

#include "brick.h"
#include <stdio.h>

#define SENSOR_GYRO IN2

int main() {
	if(!brick_init()) {
		printf("Fel uppstod i brick_init().\n");
		return 1;
	}

	if(sensor_is_plugged(SENSOR_GYRO, SENSOR_TYPE__NONE_)) {
		printf("Calibrating gyro sensor. Don't touch or move the robot.\n");
		sleep_ms(500);

		gyro_set_mode_gyro_cal(SENSOR_GYRO);
		sleep_ms(2000);

		/* Sätter läget på gyron till att mäta både vinkel och rotationshastighet. */
		gyro_set_mode_gyro_g_and_a(SENSOR_GYRO);

		/* Gör mätning på robot för att nollställa gyro. */
		sensor_get_value0(SENSOR_GYRO, 0);
		sensor_get_value1(SENSOR_GYRO, 0);

		while(1) {
			/*
			 * Gyro sensorn lägger in vinkeln i value0 och rotationshastighet i value1.
			 * Vinkel mäts i grader från -32768 grader till 32767 grader. Rotationshastighet mäts som högst 440 grader/s.
			 */
			float angle = sensor_get_value0(SENSOR_GYRO, 0);
			float rotation_speed = sensor_get_value1(SENSOR_GYRO, 0);

			printf("Vinkel: %f grader, rotationshastighet: %f grader/s\n", angle, rotation_speed);
			sleep_ms(100);
		}
	}
	else {
		printf("Gyro sensor not plugged in.\n");
	}

	brick_uninit();
	return 0;
}