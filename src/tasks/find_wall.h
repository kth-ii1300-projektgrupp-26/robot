/*
 * Den här filen innehåller funktioner för den första delen av programmet,
 * där roboten ska hitta den närmaste väggen och vända sig mot den.
 *
 * När uppgiften är klar befinner sig roboten ca 50 cm från väggen och är
 * redo att vända.
 */

#ifndef FIND_WALL_H
#define FIND_WALL_H

#include <stdbool.h>

/* Utför uppgiften "Hitta vägg och justera". */
void task_find_wall(bool to_other_side);

/*
 * Roboten roterar ett helt varv och hittar den vinkeln då
 * "något" finns närmast enligt sensor.
 *
 * Returnerar vinkeln som hittades.
 */
float subtask_find_closest_wall_angle();

/*
 * Om to_other_side = true så måste roboten flytta sig till
 * den andra sidan av korridoren, ca 50 cm från väggen.
 *
 * När den här funktionen används ska roboten vara riktad
 * mot väggen på andra sidan korridoren.
 */
void subtask_move_to_other_side();

#endif