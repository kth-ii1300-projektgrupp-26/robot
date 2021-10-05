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

	//subtask_setup_move(direction);
	while(subtask_update_move()) {

	}

	// stoppa motor
}

void subtask_setup_move(direction_t direction) {
	/* TODO */
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