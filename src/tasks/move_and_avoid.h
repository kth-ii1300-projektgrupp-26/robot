/*
 * Den här filen innehåller funktioner för den andra delen av programmet,
 * där roboten ska åka 250 cm och undvika objekt på vägen.
 *
 * När uppgiften är klar befinner sig roboten ca 50 cm från väggen vid
 * slutpunkten. Roboten är riktad åt det hållet som den skulle åka.
 */

#ifndef MOVE_AND_AVOID_H
#define MOVE_AND_AVOID_H

#include "movement.h"

/* Utför uppgiften "Åk och undvik objekt". */
void task_move_and_avoid(direction_t direction);

#endif