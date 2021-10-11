/*
 * Den här filen innehåller funktioner där roboten ska släppa boken på rätt plats.
 *
 * När uppgiften är klar har roboten släppt boken och är redo att åka tillbaka
 * till startpunkten.
 */

#ifndef HOLD_BOOK_H
#define HOLD_BOOK_H

#include "movement.h"

/* Sätter på motorer för att hålla boken. */
void task_hold_book();

/* Utför uppgiften "Släpp av bok". */
void task_drop_book(direction_t direction);

#endif