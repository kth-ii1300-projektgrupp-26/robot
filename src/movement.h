#include "brick.h"

/*
 * "Direction type".
 * Väljer om roboten behöver åka till vänster eller höger relativt väggen
 * som den har framför sig i början.
 */
typedef enum {
	DIRECTION_LEFT,
	DIRECTION_RIGHT
} direction_t;