#!/bin/bash
# Kompilerar alla *.c filer till ett körbart program som ligger i bin/mailman.
GCC_ARGS="-lev3dev-c -Isrc -Wall -Werror-implicit-function-declaration"

mkdir -p build bin

# Sensors
mkdir -p build/sensors
gcc -c src/sensors/gyro.c $GCC_ARGS -o build/sensors/gyro.o
gcc -c src/sensors/ultrasonic.c $GCC_ARGS -o build/sensors/ultrasonic.o

# Tasks
mkdir -p build/tasks
gcc -c src/tasks/drop_book.c $GCC_ARGS -o build/tasks/drop_book.o
gcc -c src/tasks/find_wall.c $GCC_ARGS -o build/tasks/find_wall.o
gcc -c src/tasks/move_and_avoid.c $GCC_ARGS -o build/tasks/move_and_avoid.o

# General
gcc -c src/movement.c $GCC_ARGS -o build/movement.o
gcc -c src/main.c $GCC_ARGS -o build/main.o

gcc build/main.o \
	build/movement.o \
	\
	build/tasks/drop_book.o \
	build/tasks/find_wall.o \
	build/tasks/move_and_avoid.o \
	\
	build/sensors/gyro.o \
	build/sensors/ultrasonic.o \
	\
	$GCC_ARGS \
	-o bin/mailman

echo "Done!"