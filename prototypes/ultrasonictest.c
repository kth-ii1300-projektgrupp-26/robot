#include "brick.h"
#include <stdio.h>
#define MOTOR_LEFT OUTB
#define MOTOR_RIGHT OUTC

#define MOTOR_BOTH (MOTOR_LEFT | MOTOR_RIGHT)
#define SENSOR_ULTRASONIC IN3

int main() {
	if(!brick_init()) {
		printf("Fel uppstod i brick_init().\n");
		return 1;
	}
	
	if(tacho_is_plugged(MOTOR_BOTH, TACHO_TYPE__NONE_)) {
		int max_speed = tacho_get_max_speed(MOTOR_LEFT, 0);

		tacho_reset(MOTOR_BOTH);

		printf("Moving forward for one second...\n");

		tacho_set_speed_sp(MOTOR_BOTH, max_speed * 0.5);
		tacho_run_forever(MOTOR_BOTH);
	

	if(sensor_is_plugged(SENSOR_ULTRASONIC, SENSOR_TYPE__NONE_)) {
		
		us_set_mode_us_dist_cm(SENSOR_ULTRASONIC);

		while(1) {
			
			float distance = sensor_get_value0(SENSOR_ULTRASONIC, 0) / 10;

			printf("Distans till vägg: %f cm\n", distance);
			if(distance == 30){
			sleep_ms(1000);
		tacho_stop(MOTOR_BOTH);  
		
			}
			sleep_ms(500);
		}
	}
	else {
		printf("Ultrasonic sensor not plugged in.\n");
	}

	brick_uninit();
	return 0;
}