#include "../timer.h"

#include <arch/timer.h>
#include <arch/types.h>

float delta_time = 0; 
unsigned int new_time, old_time; 

void time_init()
{
	
}

void time_update()
{
	old_time = new_time; 
	new_time = time_get_tick(); 
	delta_time = (new_time - old_time)*0.001f; 
}

unsigned long time_get_tick()
{
	return (unsigned long) timer_ms_gettime64(); 
}

float time_delta_time()
{
	return delta_time; 
}
