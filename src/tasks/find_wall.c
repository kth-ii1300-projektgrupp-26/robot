#include "tasks/find_wall.h"

#include <stdio.h>

#include "movement.h"
#include "ports.h"

#include "sensors/ultrasonic.h"
#include "sensors/gyro.h"

void task_find_wall(bool to_other_side) {
	float closest_angle = subtask_find_closest_wall_angle();

	if(closest_angle == NO_WALL_FOUND) {
		/* TODO: error */
	}
	else {
		if(360 - closest_angle < closest_angle) {
			rotate_robot(-360 + closest_angle);
		}
		else {
			rotate_robot(closest_angle);
		}

		if(to_other_side) {
			subtask_move_to_other_side();
		}

		subtask_control_distance_to_wall();
	}

	reset_gyro_sensor();
}

float subtask_find_closest_wall_angle() {
	/* NO_WALL_FOUND = inget hittat än */
	float closest_angle = NO_WALL_FOUND;
	float closest_angle_distance = NO_WALL_FOUND;
	float angle = sensor_get_value0(SENSOR_GYRO, 0);

	/* Sätter roboten till att rotera höger. */
	int speed = tacho_get_max_speed(MOTOR_LEFT, 0) * 0.1; /* TODO: prova lägre hastighet och se om det är bättre. */
	tacho_set_speed_sp(MOTOR_LEFT, speed);
	tacho_set_speed_sp(MOTOR_RIGHT, -speed);

	tacho_run_forever(MOTOR_BOTH);

	while(angle < 360 /* ett helt varv */) {
		if(can_find_object()) {
			float distance = get_distance_to_object();

			/*
			 * Om vi inte har hittat någon vägg tidigare ELLER om det är kortare
			 * till den här väggen sätter vi det här som den nya "närmaste väggen".
			 */
			if(closest_angle_distance == NO_WALL_FOUND || distance <= closest_angle_distance) {
				closest_angle = angle;
				closest_angle_distance = distance;
			}
		}

		angle = sensor_get_value0(SENSOR_GYRO, 0);
	}

	tacho_stop(MOTOR_BOTH);
	return closest_angle;
}

void subtask_move_to_other_side() {
	/* Roboten är nu vänd mot den andra väggen. */
	rotate_robot(180);

	int speed = tacho_get_max_speed(MOTOR_LEFT, 0) * 0.25;
	tacho_set_speed_sp(MOTOR_BOTH, speed);

	tacho_run_forever(MOTOR_BOTH);

	while(!can_find_object() || get_distance_to_object() > 0.5) {
		/* Vänta på att roboten är framme. */
	}

	tacho_stop(MOTOR_BOTH);
}

void subtask_control_distance_to_wall() {
	float distance = sensor_get_value0(SENSOR_ULTRASONIC, 0) / 1000;
	if(can_find_object()){
		// minst 45 cm högst 55 cm
		if(distance < 0.45 || distance > 0.55)
		{
			int max_speed = tacho_get_max_speed(MOTOR_LEFT, 0) * 0.1;

		tacho_reset(MOTOR_BOTH);

		printf("Moving forward for one second...\n");

		tacho_set_speed_sp(MOTOR_BOTH, -max_speed * 0.1);
		tacho_run_forever(MOTOR_BOTH);
			tacho_run_forever(MOTOR_BOTH);
		}
		
		
	}
	if (get_distance_to_object())
	{
		
	}
	
}