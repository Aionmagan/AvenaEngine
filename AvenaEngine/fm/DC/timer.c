#include "../timer.h"

#include <arch/timer.h>
#include <arch/types.h>

#include <time.h>

#define LOW_LIMIT 0.0167
#define HIGH_LIMIT 0.1

float delta_time = 0; 
unsigned int new_time = 0, old_time; 

void time_init()
{
	srand(time(NULL));
}

void time_update()
{
	old_time = new_time; 
	new_time = time_get_tick(); 
	delta_time = (new_time - old_time)*0.001f; 
	
	if (delta_time < LOW_LIMIT) 
		delta_time = LOW_LIMIT; 
	else if (delta_time > HIGH_LIMIT)
		delta_time = HIGH_LIMIT; 		
}

unsigned long time_get_tick()
{
	return (unsigned long) timer_ms_gettime64(); 
}

float time_delta_time()
{
	return delta_time; 
}
