/*
 * Den här filen innehåller funktioner där roboten ska släppa boken på rätt plats.
 *
 * När uppgiften är klar har roboten släppt boken och är redo att åka tillbaka
 * till startpunkten.
 */

#ifndef DROP_BOOK_H
#define DROP_BOOK_H

/* Utför uppgiften "Släpp av bok". */
void task_drop_book();

/*
 * När roboten har nått fram till destination så är den ca 50 cm från väggen.
 * I den här funktionen måste roboten rotera så att den kan släppa boken bakåt,
 * och den måste se till så att boken (inte roboten själv) hamnar 0-30 cm från
 * väggen.
 */
void subtask_position_for_drop();

/*
 * I den här funktionen används den lilla motorn på roboten för att släppa boken.
 * subtask_position_for_drop() ser till så att boken hamnar rätt.
 */
void subtask_drop_with_motor();

#endif