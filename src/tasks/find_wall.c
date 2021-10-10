#include "tasks/find_wall.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "movement.h"
#include "ports.h"

#include "sensors/ultrasonic.h"
#include "sensors/gyro.h"

void task_find_wall(bool to_other_side) {
	/* TODO: testa */
	/* float closest_angle_left = subtask_find_closest_wall_angle(DIRECTION_LEFT); */
	float closest_angle_right = subtask_find_closest_wall_angle(DIRECTION_RIGHT);

	if(closest_angle_right == NO_WALL_FOUND) {
		printf("No wall found.\n");
		exit(1);
	}
	else {
		rotate_robot(closest_angle_right);

		if(to_other_side) {
			subtask_move_to_other_side();
		}

		subtask_control_distance_to_wall();
	}
}

float subtask_find_closest_wall_angle(direction_t rotation_direction) {
	reset_gyro_sensor();

	/* NO_WALL_FOUND = inget hittat än */
	float closest_angle = NO_WALL_FOUND;
	float closest_angle_distance = NO_WALL_FOUND;

	/* Sätter roboten till att rotera vänster eller höger. */
	int speed = tacho_get_max_speed(MOTOR_LEFT, 0) * ROTATION_SPEED;
	if(rotation_direction == DIRECTION_LEFT) {
		speed = -speed;
	}

	tacho_set_speed_sp(MOTOR_LEFT, speed);
	tacho_set_speed_sp(MOTOR_RIGHT, -speed);

	tacho_run_forever(MOTOR_BOTH);

	float angle = sensor_get_value0(SENSOR_GYRO, 0);
	printf("subtask_find_closest_wall_angle(): angle at start %f\n", angle);

	while(true) {
		if(rotation_direction == DIRECTION_LEFT && angle <= -360) {
			break;
		}
		if(rotation_direction == DIRECTION_RIGHT && angle >= 360) {
			break;
		}
		if(can_find_object()) {
			float distance = get_distance_to_object();

			/*
			 * Om vi inte har hittat någon vägg tidigare ELLER om det är kortare
			 * till den här väggen sätter vi det här som den nya "närmaste väggen".
			 */
			if(closest_angle_distance == NO_WALL_FOUND || distance < closest_angle_distance) {
				closest_angle = angle;
				closest_angle_distance = distance;
			}
		}

		angle = sensor_get_value0(SENSOR_GYRO, 0);
	}

	printf("subtask_find_closest_wall_angle(): angle at end %f\n", angle);
	printf("subtask_find_closest_wall_angle(): closest angle %f\n", closest_angle);
	printf("subtask_find_closest_wall_angle(): closest angle distance %f\n", closest_angle_distance);

	tacho_stop(MOTOR_BOTH);
	sleep_ms(500);

	if(rotation_direction == DIRECTION_LEFT) {
		/* TODO: fel? */
		return 360 - fabs(closest_angle);
	}
	else {
		return closest_angle;
	}
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
	sleep_ms(200);
}

void subtask_control_distance_to_wall() {
	/* hur långt roboten är till väggen nu */
	float distance = sensor_get_value0(SENSOR_ULTRASONIC, 0) / 1000;
	int max_speed = tacho_get_max_speed(MOTOR_LEFT, 0) * 0.3;

	if(can_find_object()){
		float distance_to_50cm;
		if(distance > 0.45 || distance < 0.55) {
		// minst 45 cm högst 55 cm

			// matte: hur långt måste den åka för att vara 50 cm från väggen?
			 distance_to_50cm = distance - 0.5;
			move(distance_to_50cm, 0.3);
		}

		sleep_ms(1000);
	}

}