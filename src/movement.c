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
	float initial_angle = sensor_get_value0(SENSOR_GYRO, 0);
	float target_angle = initial_angle + degrees;

	int initial_motor_pos_left = tacho_get_position(MOTOR_LEFT, 0);
	int initial_motor_pos_right = tacho_get_position(MOTOR_RIGHT, 0);

	/* 0.1 verkar fungera bra. Kan behöva testas mer. */
	int speed = tacho_get_max_speed(MOTOR_LEFT, 0) * 0.1;

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

	tacho_run_forever(MOTOR_BOTH);

	float angle = initial_angle;
	/* Motorer är på tills gyro sensorn säger att vi är vid exakt rätt vinkel. */
	while(angle != target_angle) {
		angle = sensor_get_value0(SENSOR_GYRO, 0);
	}

	tacho_stop(MOTOR_BOTH);

	printf("Initial angle: %f, angle: %f, difference: %f\n", initial_angle, angle, fabs(angle - initial_angle));
	printf(
		"Initial motor pos: {%d, %d}, motor pos: {%d, %d}\n",
		initial_motor_pos_left, initial_motor_pos_right,
		tacho_get_position(MOTOR_LEFT, 0), tacho_get_position(MOTOR_RIGHT, 0)
	);

	motor_position_t difference;
	/* Hur många grader vänster motor har roterat. */
	difference.left = tacho_get_position(MOTOR_LEFT, 0) - initial_motor_pos_left;
	/* Hur många grader höger motor har roterat. */
	difference.right = tacho_get_position(MOTOR_RIGHT, 0) - initial_motor_pos_right;

	return difference;
}

void move (float distance, float speed) {
	int max_speed = tacho_get_max_speed(MOTOR_BOTH,0);
	tacho_set_speed_sp(MOTOR_BOTH, max_speed * speed);

	int current_rot = tacho_get_position(MOTOR_LEFT, 0);
	int goal_rot = meter_to_wheel_rotation(distance) + current_rot;

/*use run to rel or fix an if statment*/
	while (current_rot < goal_rot ) 
	{
		tacho_run_forever(MOTOR_BOTH);
		current_rot = tacho_get_position(MOTOR_LEFT, 0);
	}
	tacho_stop(MOTOR_BOTH);

{


}