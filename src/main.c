#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "brick.h"
#include "movement.h"
#include "ports.h"

#include "sensors/gyro.h"
#include "sensors/ultrasonic.h"

#include "tasks/hold_book.h"
#include "tasks/find_wall.h"
#include "tasks/move_and_avoid.h"

#include "sounds.h"

int main() {
	direction_t direction = BUILD_DIRECTION;
	bool to_other_side = BUILD_TO_OTHER_SIDE;

	if(!brick_init()) {
		printf("Error in brick_init().\n");
		system("beep -f 200 -l 1000");
		return 1;
	}

	/* Kontrollera att motorer sitter i. */
	if(!tacho_is_plugged(MOTOR_BOTH, TACHO_TYPE__NONE_)) {
		printf("Left and/or right motor not plugged in.\n");
		system("beep -f 200 -l 1000");
		return 1;
	}

	/* Kontrollerar att gyro sensorn sitter i. */
	if(!sensor_is_plugged(SENSOR_GYRO, SENSOR_TYPE__NONE_)) {
		printf("Gyro sensor not plugged in.\n");
		system("beep -f 200 -l 1000");
		return 1;
	}

	/* Kontrollerar att ultrasonic sensorn sitter i. */
	if(!sensor_is_plugged(SENSOR_ULTRASONIC, SENSOR_TYPE__NONE_)) {
		printf("Ultrasonic sensor not plugged in.\n");
		system("beep -f 200 -l 1000");
		return 1;
	}

	/* Ställ in motorer i rätt läge. */
	tacho_reset(MOTOR_BOTH);
	tacho_set_stop_action_brake(MOTOR_BOTH);

	/* Sätter läget på ultrasonic sensorn till att mäta kontinuerligt i centimeter. */
	us_set_mode_us_dist_cm(SENSOR_ULTRASONIC);

	/*backing_sound();*/

	printf("Running task_hold_book()!\n");
	task_hold_book();
	printf("Running task_find_wall()!\n");
	task_find_wall(to_other_side);

	/*
	 * När roboten har åkt till andra sidan har den bytt perspektiv så vänster blir
	 * höger och höger blir vänster.
	 */
	if(to_other_side) {
		if(direction == DIRECTION_LEFT) {
			direction = DIRECTION_RIGHT;
		}
		else if(direction == DIRECTION_RIGHT) {
			direction = DIRECTION_LEFT;
		}
	}

	printf("Running task_move_and_avoid()!\n");
	task_move_and_avoid(direction);

	/* Kör en till find wall för att säkerställa att vi pekar mot väggen. */
	subtask_control_distance_to_wall(0.15);

	float closest_angle_approach_left = subtask_find_closest_wall_angle(DIRECTION_LEFT);
	float closest_angle_approach_right = subtask_find_closest_wall_angle(DIRECTION_RIGHT);

	float angle = (closest_angle_approach_left + closest_angle_approach_right) / 2;
	if(360 - angle < angle) {
		rotate_robot(-360 + angle);
	}
	else {
		rotate_robot(angle);
	}

	printf("Running task_drop_book()!\n");
	task_drop_book(direction);

	/* Vänd håll och kör programmet igen för att återgå till startpunkt. */
	if(direction == DIRECTION_LEFT) {
		direction = DIRECTION_RIGHT;
	}
	else if(direction == DIRECTION_RIGHT) {
		direction = DIRECTION_LEFT;
	}

	if(to_other_side) {
		subtask_move_to_other_side();

		if(direction == DIRECTION_LEFT) {
			direction = DIRECTION_RIGHT;
		}
		else if(direction == DIRECTION_RIGHT) {
			direction = DIRECTION_LEFT;
		}
	}

	printf("Running task_move_and_avoid again()!\n");
	task_move_and_avoid(direction);

	subtask_control_distance_to_wall(0.4);

	brick_uninit();
	return 0;
}