#include "tasks/find_wall.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "movement.h"
#include "ports.h"

#include "sensors/ultrasonic.h"
#include "sensors/gyro.h"

void task_find_wall(bool to_other_side) {
	/* Försök 1: 50 cm från väggen */
	float closest_angle_pass1 = subtask_find_closest_wall_angle(DIRECTION_RIGHT);

	if(closest_angle_pass1 == NO_WALL_FOUND) {
		system("beep -f 200 -l 1000");
		printf("No wall found.\n");
		exit(1);
	}

	/* Om det är kortare att gå moturs än medurs. */
	if(360 - closest_angle_pass1 < closest_angle_pass1) {
		/* Starta vid minus ett helt varv och "ta bort" closest wall angle. */
		rotate_robot(-360 + closest_angle_pass1);
	}
	else {
		rotate_robot(closest_angle_pass1);
	}

	subtask_control_distance_to_wall(0.15);

	/* Försök 2: 15 cm från väggen */
	float closest_angle_approach_left = subtask_find_closest_wall_angle(DIRECTION_LEFT);
	float closest_angle_approach_right = subtask_find_closest_wall_angle(DIRECTION_RIGHT);

	/*
	 * Ta ett medelvärde på den närmaste punkten då roboten närmar sig från vänster
	 * och höger.
	 *
	 * Anledningen till att det här ger bättre resultat är för att roboten kan råka hitta
	 * en "tidigare" punkt på väggen än exakt medelpunkt, så medelvärdet av de här två punkterna
	 * borde teoretisk sett hamna mitt på väggen.
	 */
	float angle = (closest_angle_approach_left + closest_angle_approach_right) / 2;
	if(360 - angle < angle) {
		rotate_robot(-360 + angle);
	}
	else {
		rotate_robot(angle);
	}

	if(to_other_side) {
		subtask_move_to_other_side();
	}

	subtask_control_distance_to_wall(0.4);
}

float subtask_find_closest_wall_angle(direction_t rotation_direction) {
	reset_gyro_sensor();

	/* NO_WALL_FOUND = inget hittat än */
	float closest_angle = NO_WALL_FOUND;
	float closest_angle_distance = NO_WALL_FOUND;

	/* Sätter roboten till att rotera vänster eller höger. */
	int speed = tacho_get_max_speed(MOTOR_LEFT, 0) * ROTATION_SPEED;

	/* Vänster = negativ speed */
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
		/*
		 * Den här funktionen ska alltid ge en vinkel som roboten kan använda när den
		 * roterar åt höger (rotate_robot med positivt värde ger rotation åt höger).
		 *
		 * En positiv vinkel ges av ett helt varv på cirkeln minus absolutbeloppet av
		 * vinkeln "åt vänster". Så om vinkel är -30 så blir resultatet 360 - |-30| = 330.
		 * Att rotera 330 åt höger är samma som att rotera -30 åt vänster.
		 */
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

	while(!can_find_object() || get_distance_to_object() > 0.4) {
		/* Vänta på att roboten är framme. */
	}

	tacho_stop(MOTOR_BOTH);
	sleep_ms(200);
}

void subtask_control_distance_to_wall(float target_distance) {
	/* hur långt roboten är till väggen nu */
	float distance = sensor_get_value0(SENSOR_ULTRASONIC, 0) / 1000;
	int max_speed = tacho_get_max_speed(MOTOR_LEFT, 0) * 0.2;

	if(can_find_object()){
		float distance_to_50cm;
		if(distance > target_distance - 0.05 || distance < target_distance + 0.05) {
		// minst 45 cm högst 55 cm

			// matte: hur långt måste den åka för att vara 50 cm från väggen?
			 distance_to_50cm = distance - target_distance;
			move(distance_to_50cm, 0.2);
		}

		sleep_ms(1000);
	}

}