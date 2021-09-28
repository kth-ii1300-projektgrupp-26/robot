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
		/* TODO: hitta den närmaste vägen istället för alltid rotera höger*/
		rotate_robot(closest_angle);
		reset_gyro_sensor();
	}

	subtask_control_distance_to_wall();
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
	/* TODO */
}

void subtask_control_distance_to_wall() {
	/* TODO */
}