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

/*
 * När roboten har nått fram till destination så är den ca 50 cm från väggen.
 * I den här funktionen måste roboten rotera så att den kan släppa boken bakåt,
 * och den måste se till så att boken (inte roboten själv) hamnar 0-30 cm från
 * väggen.
 */
void subtask_position_for_drop();

#endif