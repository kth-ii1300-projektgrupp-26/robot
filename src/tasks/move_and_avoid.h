/*
 * Den här filen innehåller funktioner för den andra delen av programmet,
 * där roboten ska åka 250 cm och undvika objekt på vägen.
 *
 * När uppgiften är klar befinner sig roboten ca 50 cm från väggen vid
 * slutpunkten. Roboten är riktad åt det hållet som den skulle åka.
 */

#ifndef MOVE_AND_AVOID_H
#define MOVE_AND_AVOID_H

#include <stdbool.h>
#include "movement.h"

/* Utför uppgiften "Åk och undvik objekt". */
void task_move_and_avoid(direction_t direction);

/*
 * Gör roboten redo för leverans genom att vända sig åt rätt håll och
 * ställa in alla motorer (vänster, höger och "medium").
 */
void subtask_setup_move(direction_t direction);

/*
 * Den här funktionen ska köras i en while-loop och kontrollera om/hur
 * roboten ska röra på sig. Om inte så returnerar den false.
 */
bool subtask_update_move();

/*
 * Räknar ut hur långt roboten har kvar till målet i meter. Den här
 * funktionen kollar MOTOR_LEFT och MOTOR_RIGHT, men den måste också
 * ignorera så många grader som anges i ignore_degrees.
 *
 * Anledningen till att den här funktionen behöver ignorera ett visst
 * antal grader är för att rotationen av roboten inte ska räknas med
 * (om den behöver undvika hinder).
 */
float subtask_get_distance_left(motor_position_t ignore_degrees);

#endif