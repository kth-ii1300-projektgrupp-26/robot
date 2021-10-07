#include "tasks/move_and_avoid.h"
#include "movement.h"
#include "ports.h"
#include "sensors/gyro.h"



float start_rotation;
float goal_rotation;
float distance_left;



void task_move_and_avoid(direction_t direction) {
	start_rotation = tacho_get_position(MOTOR_LEFT, 0);
	goal_rotation = start_rotation + meter_to_wheel_rotation(2.5);

	subtask_setup_move(direction);
	move(2.5, 0.2);
	/*while(subtask_update_move()) {

	}*/

	// stoppa motor
}

void subtask_setup_move(direction_t direction) {

if (direction == DIRECTION_LEFT ){
rotate_robot(-90);
}
if(direction == DIRECTION_RIGHT){
	rotate_robot(90);
	}
	/*int max_speed = tacho_get_max_speed(MOTOR_LEFT, 0);

tacho_set_speed_sp(MOTOR_BOTH, max_speed * 0.3);
		tacho_run_forever(MOTOR_BOTH);*/

}

bool subtask_update_move() {
	// kolla om distance_left <= 0 och retunera false i så fall

}

float subtask_get_distance_left(motor_position_t ignore_degrees) {
	/* TODO */
	distance_left = goal_rotation - start_rotation;
	if(distance_left <= 0){
		return(false);
	}
	else{
		return(true);
		}
}