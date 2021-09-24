#include <stdio.h>

#include "brick.h"
#include "robot.h"

int main() {
	if(!brick_init()) {
		printf("Fel uppstod i brick_init().\n");
		return 1;
	}

	/* Kontrollera att motorer sitter i. */
	if(!tacho_is_plugged(MOTOR_BOTH, TACHO_TYPE__NONE_)) {
		printf("Left and/or right motor not plugged in.\n");
		return 1;
	}

	/* Ställ in motorer i rätt läge. */
	tacho_reset(MOTOR_BOTH);

	/* Kontrollerar att gyro sensorn sitter i. */
	if(!sensor_is_plugged(SENSOR_GYRO, SENSOR_TYPE__NONE_)) {
		printf("Gyro sensor not plugged in.\n");
		return 1;
	}

	/* Kontrollerar att ultrasonic sensorn sitter i. */
	if(!sensor_is_plugged(SENSOR_ULTRASONIC, SENSOR_TYPE__NONE_)) {
		printf("Ultrasonic sensor not plugged in.\n");
		return 1;
	}

	/*
	 * För att gyro sensorn ska fungera korrekt behöver den veta vart nollpunkten är
	 * (där den mäter 0 grader rotation) och den behöver även veta vad som räknas att
	 * roboten är "stilla".
	 *
	 * gyro_set_mode_gyro_cal sätter gyron i ett kalibreringsläge. Programmet väntar en
	 * sekund och där roboten befinner sig efter det räknas som nollpunkten för sensorn.
	 *
	 * Referens: ev3lessons.com, docs.ev3dev.org
	 */
	printf("Calibrating gyro sensor. Don't touch or move the robot.\n");
	sleep_ms(1000);

	/* TODO: Det här behöver testas på roboten. */
	gyro_set_mode_gyro_cal(SENSOR_GYRO);
	sleep_ms(1000);

	/* Sätter läget på gyron till att mäta både vinkel och rotationshastighet. */
	gyro_set_mode_gyro_g_and_a(SENSOR_GYRO);

	/* Sätter läget på ultrasonic sensorn till att mäta kontinuerligt i centimeter. */
	us_set_mode_us_dist_cm(SENSOR_ULTRASONIC);

	printf("Done! The robot is now ready for delivery.\n");

	brick_uninit();
	return 0;
}