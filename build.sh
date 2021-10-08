#!/bin/bash
# Kompilerar alla *.c filer till ett körbart program som ligger i bin/mailman.

# Docker kräver att den här GCC används
GCC=arm-linux-gnueabi-gcc
GCC_ARGS="-lev3dev-c -lm -Isrc -I/usr/local/include -Wall -Werror-implicit-function-declaration"

rm -R build bin
mkdir -p build bin

# Sensors
mkdir -p build/sensors
$GCC -c src/sensors/gyro.c $GCC_ARGS -o build/sensors/gyro.o
$GCC -c src/sensors/ultrasonic.c $GCC_ARGS -o build/sensors/ultrasonic.o

# Tasks
mkdir -p build/tasks
$GCC -c src/tasks/hold_book.c $GCC_ARGS -o build/tasks/hold_book.o
$GCC -c src/tasks/find_wall.c $GCC_ARGS -o build/tasks/find_wall.o
$GCC -c src/tasks/move_and_avoid.c $GCC_ARGS -o build/tasks/move_and_avoid.o

# General
$GCC -c src/movement.c $GCC_ARGS -o build/movement.o
$GCC -c src/sounds.c $GCC_ARGS -o build/sounds.o

# Bygg fyra versioner av main.c som ger de fyra programmen/uppgifterna
$GCC -c src/main.c -DBUILD_DIRECTION=DIRECTION_RIGHT -DBUILD_TO_OTHER_SIDE=false $GCC_ARGS -o build/main_1.o
$GCC -c src/main.c -DBUILD_DIRECTION=DIRECTION_LEFT -DBUILD_TO_OTHER_SIDE=false $GCC_ARGS -o build/main_2.o
$GCC -c src/main.c -DBUILD_DIRECTION=DIRECTION_RIGHT -DBUILD_TO_OTHER_SIDE=true $GCC_ARGS -o build/main_3.o
$GCC -c src/main.c -DBUILD_DIRECTION=DIRECTION_LEFT -DBUILD_TO_OTHER_SIDE=true $GCC_ARGS -o build/main_4.o

# Program 1
$GCC build/main_1.o \
	build/movement.o \
	build/sounds.o \
	\
	build/tasks/* \
	build/sensors/* \
	\
	$GCC_ARGS \
	-o bin/mailman_task1_R

# Program 2
$GCC build/main_2.o \
	build/movement.o \
	build/sounds.o \
	\
	build/tasks/* \
	build/sensors/* \
	\
	$GCC_ARGS \
	-o bin/mailman_task2_L

# Program 3 (os = other side)
$GCC build/main_3.o \
	build/movement.o \
	build/sounds.o \
	\
	build/tasks/* \
	build/sensors/* \
	\
	$GCC_ARGS \
	-o bin/mailman_task3_R_OS

# Program 4 (os = other side)
$GCC build/main_4.o \
	build/movement.o \
	build/sounds.o \
	\
	build/tasks/* \
	build/sensors/* \
	\
	$GCC_ARGS \
	-o bin/mailman_task4_L_OS

echo "Done!"