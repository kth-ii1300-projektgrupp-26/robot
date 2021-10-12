#include "tasks/hold_book.h"
#include "tasks/find_wall.h"
#include "ports.h"
#include "brick.h"
#include "movement.h"

#include <stdlib.h>

void task_drop_book(direction_t direction) {
	int motor_medium_speed = tacho_get_max_speed(MOTOR_MEDIUM,0);
	int motor_medium_degree = tacho_get_position(MOTOR_MEDIUM,0);

	/* 1. Sänk ner motorn och håll i 2 sekunder */
	tacho_set_speed_sp(MOTOR_MEDIUM, motor_medium_speed * -1);
	tacho_run_forever(MOTOR_MEDIUM);
	sleep_ms(2000);
	tacho_stop(MOTOR_MEDIUM);

	system("beep -f 200 -l 1000");

	/* 2. Höj upp motorn lite för att inte stoppa hjulen  */
	tacho_set_speed_sp(MOTOR_MEDIUM, motor_medium_speed * 0.25);
	tacho_run_forever(MOTOR_MEDIUM);
	sleep_ms(200);
	tacho_stop(MOTOR_MEDIUM);

	/* 3. Åk bakåt så att vi vet att roboten inte kör fast i boken */
	move(-0.1, 0.2);

	/* 4. Höj upp MOTOR_MEDIUM igen så att den inte blockerar ultrasonic sensorn */
	task_hold_book();
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