#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdbool.h>

/*
 * EV3 Ultrasonic Sensor kan mäta mellan 0 och 250 cm, så om det inte
 * finns någon vägg eller annat objekt högst 250 cm från roboten
 * returnerar den här funktionen false.
 */
bool can_find_object();

/*
 * Om can_find_object() = true returnerar den här funktionen distansen
 * till den närmaste väggen i meter.
 */
float get_distance_to_object();

#endif