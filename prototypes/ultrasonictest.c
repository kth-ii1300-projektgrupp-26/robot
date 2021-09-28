/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
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
		/* Sätter läget på ultrasonic sensorn till att mäta kontinuerligt i centimeter. */
		us_set_mode_us_dist_cm(SENSOR_ULTRASONIC);

		while(1) {
			/*
			 * Ultrasonic sensorn lägger in längden från en vägg i value0.
			 * Den mäter med en decimal så värdet måste delas med 10 för att få centimeter.
			 */
			float distance = sensor_get_value0(SENSOR_ULTRASONIC, 0) / 10;

			printf("Distans till vägg: %f cm\n", distance);
			if(distance == 30){
			sleep_ms(1000);
		tacho_stop(MOTOR_BOTH);  
		
			}
		
		  }
    	}
	}
	else {
		printf("Ultrasonic sensor not plugged in.\n");
	}

	brick_uninit();
	return 0;
}