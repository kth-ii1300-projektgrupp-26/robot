#ifndef GYRO_H
#define GYRO_H

/*
 * Kalibrerar gyro sensorn. Det här gör att punkten där roboten
 * befinner sig nu räknas som nollpunkten (alltså att den mäter 0 grader).
 *
 * Den här funktionen ska endast användas när roboten är helt still.
 */
void reset_gyro_sensor();

#endif