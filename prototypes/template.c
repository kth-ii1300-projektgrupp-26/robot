/*
 * Exempelfil för att programmera LEGO-roboten.
 * Skapad av Hannes Mann 2021-09-13.
 *
 * Baserat på exempel i Canvas: https://canvas.kth.se/courses/28714/files/4345566
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

	/* Kod här. */

	brick_uninit();
	return 0;
}