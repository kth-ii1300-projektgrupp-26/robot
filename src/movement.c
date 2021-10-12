#include "movement.h"
#include "brick.h"

#include <stdio.h>
#include <math.h>

#include "ports.h"
#include "sensors/gyro.h"

float wheel_rotation_to_meter(float rotation) {
	float Distance = (WHEEL_CIRCUMFERENCE_METER * rotation) / 360;
	return(Distance);
}

float meter_to_wheel_rotation(float length)
{
	float Degree = (length * 360) / WHEEL_CIRCUMFERENCE_METER;
	return(Degree);
}

motor_position_t rotate_robot(float degrees) {
	reset_gyro_sensor();

	motor_position_t initial_motor_pos;
	initial_motor_pos.left = tacho_get_position(MOTOR_LEFT, 0);
	initial_motor_pos.right = tacho_get_position(MOTOR_RIGHT, 0);

	int speed = tacho_get_max_speed(MOTOR_LEFT, 0) * ROTATION_SPEED;

	/*
	 * Om roboten ska rotera åt vänster åker vänster hjul bakåt och höger hjul framåt.
	 * Om roboten ska rotera åt höger åker vänster hjul framåt och höger hjul bakåt.
	 */
	if(degrees < 0) {
		tacho_set_speed_sp(MOTOR_LEFT, -speed);
		tacho_set_speed_sp(MOTOR_RIGHT, speed);
	}
	else if(degrees > 0) {
		tacho_set_speed_sp(MOTOR_LEFT, speed);
		tacho_set_speed_sp(MOTOR_RIGHT, -speed);
	}
	/* Vi gör inget om degrees == 0. */
	else if((int)degrees == 0) {
		motor_position_t zero;
		zero.left = 0;
		zero.right = 0;

		return zero;
	}

	tacho_run_forever(MOTOR_BOTH);

	float angle = sensor_get_value0(SENSOR_GYRO, 0);
	/* Motorer är på tills gyro sensorn säger att vi är vid exakt rätt vinkel. */
	while(true) {
		/* Vi gör om till int för att runda av talen. */
		/* TODO: om det här inte fungerar gå tillbaka till (int)degrees == (int)angle */
		if(degrees > 0 && (int)angle >= (int)degrees) {
			break;
		}
		if(degrees < 0 && (int)angle <= (int)degrees) {
			break;
		}

		angle = sensor_get_value0(SENSOR_GYRO, 0);
	}

	tacho_stop(MOTOR_BOTH);

	motor_position_t difference;
	/* Hur många grader vänster motor har roterat. */
	difference.left = tacho_get_position(MOTOR_LEFT, 0) - initial_motor_pos.left;
	/* Hur många grader höger motor har roterat. */
	difference.right = tacho_get_position(MOTOR_RIGHT, 0) - initial_motor_pos.right;

	return difference;
}

void move (float distance, float speed) {
	int max_speed = tacho_get_max_speed(MOTOR_LEFT,0);
	tacho_set_speed_sp(MOTOR_BOTH, max_speed * speed);

	int current_rot = tacho_get_position(MOTOR_LEFT, 0);
	printf("MOTOR_LEFT: %d, MOTOR_RIGHT: %d\n", tacho_get_position(MOTOR_LEFT, 0), tacho_get_position(MOTOR_RIGHT, 0));
	tacho_set_position_sp(MOTOR_BOTH, meter_to_wheel_rotation(distance));

	tacho_run_to_rel_pos(MOTOR_BOTH);

	while (tacho_get_state(MOTOR_LEFT) != 0 && tacho_get_state(MOTOR_RIGHT) != 0) {
		sleep_ms(10);
	}

	tacho_stop(MOTOR_BOTH);
}