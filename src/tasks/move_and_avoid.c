#include "tasks/move_and_avoid.h"
#include "movement.h"
#include "ports.h"

#include "sensors/gyro.h"
#include "sensors/ultrasonic.h"

#include <math.h>

motor_position_t goal_rotation;

/* Vi undviker bara ett objekt per leverans. */
bool has_avoided = false;

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
		/* TODO: roboten måste placera sig rätt om den har roterar till annan vinkel */
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

	tacho_set_speed_sp(MOTOR_BOTH, max_speed * 0.3);
	tacho_run_forever(MOTOR_BOTH);
}

bool subtask_update_move(direction_t direction) {
	if(!has_avoided && subtask_needs_to_avoid_object()) {
		subtask_setup_avoid(direction);
	}

	return subtask_get_distance_left() > 0;
}

float subtask_get_distance_left() {
	motor_position_t rotation_left;

	rotation_left.left =
		goal_rotation.left -
		tacho_get_position(MOTOR_LEFT, 0);

	rotation_left.right =
		goal_rotation.right -
		tacho_get_position(MOTOR_RIGHT, 0);

	/*
	 * Ta ett medelvärde av distans kvar på båda hjulen.
	 * Borde vara samma, men inte säkert.
	 */
	float average_value = (rotation_left.left + rotation_left.right) / 2;
	return wheel_rotation_to_meter(average_value);
}

bool subtask_needs_to_avoid_object() {
	return can_find_object() &&
		/* Om det finns ett objekt högst 20 cm från roboten... */
		get_distance_to_object() <= 0.2 &&
		/* ...och roboten behöver åka minst 30 cm till. */
		subtask_get_distance_left() >= 0.3;
}

void subtask_setup_avoid(direction_t direction) {
	printf("avoid: object at %f cm\n", get_distance_to_object() * 100);
	float distance_left_before_avoid = subtask_get_distance_left();

	if(direction == DIRECTION_LEFT) {
		rotate_robot(-90);
	}
	if(direction == DIRECTION_RIGHT) {
		rotate_robot(90);
	}

	move(AVOID_DISTANCE, 0.3);

	if(direction == DIRECTION_LEFT) {
		rotate_robot(90);
	}
	if(direction == DIRECTION_RIGHT) {
		rotate_robot(-90);
	}

	/* TODO: Det här är nog fel */
	float angle = atan(distance_left_before_avoid / AVOID_DISTANCE);
	if(direction == DIRECTION_LEFT) {
		rotate_robot(-angle);
	}
	if(direction == DIRECTION_RIGHT) {
		rotate_robot(angle);
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

	goal_rotation.left = start_rotation.left + meter_to_wheel_rotation(new_distance);
	goal_rotation.right = start_rotation.right + meter_to_wheel_rotation(new_distance);

	int max_speed = tacho_get_max_speed(MOTOR_LEFT, 0);

	tacho_set_speed_sp(MOTOR_BOTH, max_speed * 0.3);
	tacho_run_forever(MOTOR_BOTH);

	has_avoided = true;
}