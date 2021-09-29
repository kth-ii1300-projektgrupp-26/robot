#include "tasks/drop_book.h"
#include "ports.h"
#include "brick.h"

void task_drop_book() {
	/* TODO */
}

void subtask_position_for_drop() {
	/* TODO */
}

void subtask_drop_with_motor() {
	int motor_medium_speed = tacho_get_max_speed(MOTOR_MEDIUM,0) * 0.5;
	tacho_set_speed_sp(MOTOR_MEDIUM, motor_medium_speed *0.5);
	int motor_medium_degree = tacho_get_position(MOTOR_MEDIUM,0);

	while( motor_medium_degree < 45)
	{
		tacho_run_forever(MOTOR_MEDIUM);
		motor_medium_degree = tacho_get_position(MOTOR_MEDIUM,0);
	}
	tacho_stop(MOTOR_MEDIUM);
}
