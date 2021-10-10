#include <stdio.h>
#include "brick.h"
#include"sounds.h"


void backing_sound(){
    for(int repeats = 0; repeats < 3; repeats++){


		printf("\a");
		sleep_ms(500);
    }
}
