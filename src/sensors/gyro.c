#include <stdio.h>

#include "sensors/gyro.h"

#include "brick.h"
#include "ports.h"

void reset_gyro_sensor() {
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

	gyro_set_mode_gyro_cal(SENSOR_GYRO);
	sleep_ms(1000);

	/* Sätter läget på gyron till att mäta både vinkel och rotationshastighet. */
	gyro_set_mode_gyro_g_and_a(SENSOR_GYRO);
}