/*
 * Enkel fil för att testa roboten.
 * Skapad av Hannes Mann 2021-09-15.
 */

#include "brick.h"
#include <stdio.h>

#define MOTOR_LEFT OUTB
#define MOTOR_RIGHT OUTC

#define MOTOR_BOTH (MOTOR_LEFT | MOTOR_RIGHT)

int main() {
	if(!brick_init()) {
		printf("Fel uppstod i brick_init().\n");
		return 1;
	}

	if(tacho_is_plugged(MOTOR_BOTH, TACHO_TYPE__NONE_)) {
		int max_speed = tacho_get_max_speed(MOTOR_LEFT, 0);

		tacho_reset(MOTOR_BOTH);

		printf("Åker framåt i en sekund...\n");

		tacho_set_speed_sp(MOTOR_BOTH, max_speed * 0.5);
		tacho_run_forever(MOTOR_BOTH);
		sleep_ms(1000);
		tacho_stop(MOTOR_BOTH);

		sleep_ms(250);

		printf("Åker bakåt i en sekund...\n");

		/* -max_speed ger att båda motorer åker baklänges. */
		tacho_set_speed_sp(MOTOR_BOTH, -max_speed * 0.5);
		tacho_run_forever(MOTOR_BOTH);
		sleep_ms(1000);
		tacho_stop(MOTOR_BOTH);

		sleep_ms(250);

		printf("Snurrar runt i fem sekunder...\n");

		/*
		 * Här sätts den vänstra motorn till att åka framåt och den högra till att åka bakåt.
		 * Eftersom motorerna motverkar varandra kommer roboten att snurra runt.
		 */
		tacho_set_speed_sp(MOTOR_LEFT, max_speed * 0.5);
		tacho_set_speed_sp(MOTOR_RIGHT, -max_speed * 0.5);

		tacho_run_forever(MOTOR_BOTH);
		sleep_ms(5000);
		tacho_stop(MOTOR_BOTH);
	}
	else {
		printf("Vänster eller höger motor ej inkopplad.\n");
	}

	brick_uninit();
	return 0;
}