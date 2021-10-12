#include "tasks/move_and_avoid.h"
#include "tasks/find_wall.h"
#include "movement.h"
#include "ports.h"

#include "sensors/gyro.h"
#include "sensors/ultrasonic.h"

#include <math.h>
#include <stdio.h>

#include <stdlib.h>

motor_position_t goal_rotation;

/* Vi undviker bara ett objekt per leverans. */
bool has_avoided = false;
/* Vinkel som robot måste rotera när leveransen är över om den har undvikt objekt. */
float avoid_angle = 0;

void task_move_and_avoid(direction_t direction) {
	motor_position_t start_rotation;
	start_rotation.left = tacho_get_position(MOTOR_LEFT, 0);
	start_rotation.right = tacho_get_position(MOTOR_RIGHT, 0);

	goal_rotation.left = start_rotation.left + meter_to_wheel_rotation(2.5);
	goal_rotation.right = start_rotation.right + meter_to_wheel_rotation(2.5);

	subtask_setup_move(direction);
	while(subtask_update_move(direction)) {
	}

	if(has_avoided) {
		/* Slutför rotation som började i setup_avoid. Roboten pekar nu mot väggen. */
		if(direction == DIRECTION_LEFT) {
			rotate_robot(avoid_angle);
		}
		if(direction == DIRECTION_RIGHT) {
			rotate_robot(-avoid_angle);
		}

		/* has_avoided är en global variabel */
		has_avoided = false;
	}
	else {
		/* Vänd roboten rakt mot väggen. */
		if(direction == DIRECTION_LEFT) {
			rotate_robot(90);
		}
		if(direction == DIRECTION_RIGHT) {
			rotate_robot(-90);
		}
	}

	tacho_stop(MOTOR_BOTH);
	sleep_ms(1000);
}

void subtask_setup_move(direction_t direction) {
	if (direction == DIRECTION_LEFT ){
		rotate_robot(-90);
	}
	if(direction == DIRECTION_RIGHT){
		rotate_robot(90);
	}

	int max_speed = tacho_get_max_speed(MOTOR_LEFT, 0);

	tacho_set_speed_sp(MOTOR_BOTH, max_speed * 0.2);
	tacho_run_forever(MOTOR_BOTH);
}

bool subtask_update_move(direction_t direction) {
	if(!has_avoided && subtask_needs_to_avoid_object()) {
		subtask_setup_avoid(direction);
		has_avoided = true;
	}

	return subtask_get_distance_left() > 0;
}

float subtask_get_distance_left() {
	motor_position_t difference;

	difference.left =
		goal_rotation.left -
		tacho_get_position(MOTOR_LEFT, 0);

	difference.right =
		goal_rotation.right -
		tacho_get_position(MOTOR_RIGHT, 0);

	/*
	 * Ta ett medelvärde av distans kvar på båda hjulen.
	 * Borde vara samma, men inte säkert.
	 */
	float average_value = (difference.left + difference.right) / 2;
	return wheel_rotation_to_meter(average_value);
}

bool subtask_needs_to_avoid_object() {
	return can_find_object() &&
		/* Om det finns ett objekt högst 30 cm från roboten... */
		get_distance_to_object() <= 0.3 &&
		/* ...och roboten behöver åka minst 60 cm till. */
		subtask_get_distance_left() >= 0.6;
}

void subtask_setup_avoid(direction_t direction) {
	tacho_stop(MOTOR_BOTH);
	system("beep -f 200 -l 1000");

	printf("avoid: object at %f cm\n", get_distance_to_object() * 100);
	float distance_left_before_avoid = subtask_get_distance_left();

	if(direction == DIRECTION_LEFT) {
		rotate_robot(-90);
	}
	if(direction == DIRECTION_RIGHT) {
		rotate_robot(90);
	}

	move(AVOID_DISTANCE, 0.2);

	/* Förklaring i documentation/avoid.png (v1). */
	avoid_angle = atan(distance_left_before_avoid / AVOID_DISTANCE);
	/* Gör om angle från radianer till grader. */
	avoid_angle = avoid_angle * (180 / M_PI);

	/* Förklaring i documentation/avoid.png (v2). */
	float angle = 180 - avoid_angle;
	printf("avoid_angle: %f, angle: %f\n", avoid_angle, angle);

	if(direction == DIRECTION_LEFT) {
		rotate_robot(angle);
	}
	if(direction == DIRECTION_RIGHT) {
		rotate_robot(-angle);
	}

	float new_distance = sqrt(pow(distance_left_before_avoid, 2) + pow(AVOID_DISTANCE, 2));

	printf(
		"avoid: angle %f old distance %f cm new distance %f cm\n",
		angle,
		distance_left_before_avoid * 100,
		new_distance * 100);

	motor_position_t start_rotation;
	start_rotation.left = tacho_get_position(MOTOR_LEFT, 0);
	start_rotation.right = tacho_get_position(MOTOR_RIGHT, 0);

	/*
	 * Uppdatera hur mycket hjulen behöver rulla för att vara framme vid målet, då
	 * vi nu följer hypotenusan i en rätvinklig triangel.
	 */
	goal_rotation.left = start_rotation.left + meter_to_wheel_rotation(new_distance);
	goal_rotation.right = start_rotation.right + meter_to_wheel_rotation(new_distance);

	int max_speed = tacho_get_max_speed(MOTOR_LEFT, 0);

	tacho_set_speed_sp(MOTOR_BOTH, max_speed * 0.2);
	tacho_run_forever(MOTOR_BOTH);
}
