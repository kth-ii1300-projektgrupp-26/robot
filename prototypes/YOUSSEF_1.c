#include <stdio.h>
#include "brick.h"

#define MOTOR_R	OUTB
#define MOTOR_L	OUTC
#define GYRO	IN2
#define SENSOR	IN3

#define MOTOR ( MOTOR_R | MOTOR_L )
POOL_T US_SENSOR;

int main()
{
	int MAX_SPD;
	float angle;

	if (!brick_init()) return(1);
	printf("EV3 SAYS HELLO");
	sleep_ms(1000);

	if ( tacho_is_plugged(MOTOR, TACHO_TYPE__NONE_))
	{
		MAX_SPD = tacho_get_max_speed(MOTOR_L, 0);
		tacho_reset( MOTOR );
	}
	else
	{
		printf("Please plug the motors.");
		brick_uninit();
		return(1);
	}
	
	if (sensor_is_plugged(GYRO, SENSOR_TYPE__NONE_))
	{
		angle = sensor_get_value0(GYRO, 0);
	}
	else
	{
		printf("Gyro is not plugged.");
		return(1);
	}

/*
	US_SENSOR = sensor_search( LEGO_EV3_US_US_DIST_CM );
	us_set_mode_us_dist_cm( US_SENSOR );

	if ( gyro_)
*/

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


	/*rotate 90, -180 and 90 degrees.*/
	while ( angle != 90 )
	{
		tacho_run_forever(MOTOR_L);
	}
	tacho_stop(MOTOR);
	tacho_set_speed_sp(MAX_SPD*-0,25);
	while ( angle !=0 )
	{
		tacho_run_forever(MOTOR_L);
	}
	tacho_stop(MOTOR);
	tacho_set_speed_sp(MAX_SPD*0,25);

	while ( angle != -90)
	{
		tacho_run_forever(MOTOR_R);
	}
	tacho_stop(MOTOR_R);
	tacho_set_speed_sp(MAX_SPD*-0,25);
	while ( angle != 0)
	{
		tacho_run_forever(MOTOR_R);
	}
	tacho_stop(MOTOR);
}