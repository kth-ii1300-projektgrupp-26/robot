#!/bin/bash
# Kompilerar alla *.c filer till ett körbart program som ligger i bin/mailman.

# Docker kräver att den här GCC används
GCC=arm-linux-gnueabi-gcc
GCC_ARGS="-lev3dev-c -Isrc -I/usr/local/include -Wall -Werror-implicit-function-declaration"

mkdir -p build bin

# Sensors
mkdir -p build/sensors
$GCC -c src/sensors/gyro.c $GCC_ARGS -o build/sensors/gyro.o
$GCC -c src/sensors/ultrasonic.c $GCC_ARGS -o build/sensors/ultrasonic.o

# Tasks
mkdir -p build/tasks
$GCC -c src/tasks/drop_book.c $GCC_ARGS -o build/tasks/drop_book.o
$GCC -c src/tasks/find_wall.c $GCC_ARGS -o build/tasks/find_wall.o
$GCC -c src/tasks/move_and_avoid.c $GCC_ARGS -o build/tasks/move_and_avoid.o

# General
$GCC -c src/movement.c $GCC_ARGS -o build/movement.o
$GCC -c src/main.c $GCC_ARGS -o build/main.o

$GCC build/main.o \
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