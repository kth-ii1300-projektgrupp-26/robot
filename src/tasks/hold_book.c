#include "tasks/hold_book.h"
#include "ports.h"
#include "brick.h"
#include "movement.h"

void task_drop_book(direction_t direction) {
	subtask_position_for_drop(direction);

	int motor_medium_speed = tacho_get_max_speed(MOTOR_MEDIUM,0);
	int motor_medium_degree = tacho_get_position(MOTOR_MEDIUM,0);

	tacho_set_speed_sp(MOTOR_MEDIUM, motor_medium_speed * -1);
	tacho_run_forever(MOTOR_MEDIUM);
	sleep_ms(2000);
	tacho_stop(MOTOR_MEDIUM);
}

void task_hold_book(){
	int motor_medium_speed = tacho_get_max_speed(MOTOR_MEDIUM,0);
	int motor_medium_degree = tacho_get_position(MOTOR_MEDIUM,0);

	tacho_set_speed_sp(MOTOR_MEDIUM, motor_medium_speed);
	tacho_run_forever(MOTOR_MEDIUM);
	sleep_ms(2000);
	tacho_stop(MOTOR_MEDIUM);
	tacho_set_speed_sp(MOTOR_MEDIUM, motor_medium_speed * 0.2);
	tacho_run_forever(MOTOR_MEDIUM);

}
void subtask_position_for_drop(direction_t direction) {
	if(direction == DIRECTION_LEFT) {
		rotate_robot(90);
	}
	if(direction == DIRECTION_RIGHT) {
		rotate_robot(-90);
	}

	move(-30,0.5);
}