/*
 * Exempelfil för att programmera LEGO-roboten.
 * Skapad av Hannes Mann 2021-09-13.
 *
 * Baserat på exempel i Canvas: https://canvas.kth.se/courses/28714/files/4345566
 */

#include "brick.h"

int main() {
	if(!brick_init()) {
		/* Ett fel uppstod. */
		return 1;
	}

	/* Kod här. */

	brick_uninit();
	return 0;
}