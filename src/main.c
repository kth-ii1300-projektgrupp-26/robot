#include <stdio.h>
#include <stdbool.h>

#include "brick.h"
#include "movement.h"
#include "ports.h"

#include "sensors/gyro.h"

#include "tasks/drop_book.h"
#include "tasks/find_wall.h"
#include "tasks/move_and_avoid.h"

int main() {
	/* TODO: dessa ska kunna väljas av lärare. */
	direction_t direction = DIRECTION_LEFT;
	bool to_other_side = false;

	if(!brick_init()) {
		printf("Fel uppstod i brick_init().\n");
		return 1;
	}

	/* Kontrollera att motorer sitter i. */
	if(!tacho_is_plugged(MOTOR_BOTH, TACHO_TYPE__NONE_)) {
		printf("Left and/or right motor not plugged in.\n");
		return 1;
	}

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

	/* Ställ in motorer i rätt läge. */
	tacho_reset(MOTOR_BOTH);
	/* TODO: Testa om det här är bästa sättet att bromsa. */
	tacho_set_stop_action_brake(MOTOR_BOTH);

	/* Sätter in rätt läge på gyro sensorn. */
	reset_gyro_sensor();
	/* Sätter läget på ultrasonic sensorn till att mäta kontinuerligt i centimeter. */
	us_set_mode_us_dist_cm(SENSOR_ULTRASONIC);

	printf("Done! The robot is now ready for delivery.\n");

	task_find_wall(to_other_side);
	task_move_and_avoid(direction);
	task_drop_book();

	brick_uninit();
	return 0;
}