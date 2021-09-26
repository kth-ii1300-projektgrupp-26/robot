#include <stdio.h>
#include "brick.h"

#define MOTOR_R	OUTB
#define MOTOR_L	OUTC
#define GYRO	IN1
#define SENSOR	IN3

#define MOTOR ( MOTOR_R | MOTOR_L )
POOL_T US_SENSOR;

int main()
{
	int MAX_SPD;

	if (!brick_init()) return(1);
	printf("EV3 SAYS HELLO mF");
	sleep_ms(1000);

	if ( tacho_is_plugged(MOTOR, TACHO_TYPE__NONE_))
	{
		MAX_SPD = tacho_get_max_speed(MOTOR_L, 0);
		tacho_reset( MOTOR );
	}
	else
	{
		printf("Yo plug them mf tangs");
		brick_uninit();
		return(0);
	}

/*
	US_SENSOR = sensor_search( LEGO_EV3_US_US_DIST_CM );
	us_set_mode_us_dist_cm( US_SENSOR );
*/
	if ( gyro_)

	tacho_set_speed_sp( MOTOR, MAX_SPD*0.4);
	tacho_run_forever(MOTOR);
	sleep_ms(500);
	tachp_stop(MOTOR);

	tacho_set_speed_sp( MOTOR, MAX_SPD*-0.4);
	tacho_run_forever(MOTOR);
	sleep_ms(500);
	tachp_stop(MOTOR);

	tacho_set_speed_sp( MOTOR, MAX_SPD * 0.25);
	tacho_run_forever(MOTOR);
	sleep_ms(700);
	tacho_stop(MOTOR);


}