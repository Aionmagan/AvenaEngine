#include "../timer.h"
#include <psp2/rtc.h>

#include <time.h>

#define LOW_LIMIT 0.0167
#define HIGH_LIMIT 0.1
//SceDateTime dtime; 

float delta_time = 0; 
unsigned int tnow, tstart; 
unsigned int new_time = 0, old_time; 

void time_init()
{
	tstart = sceKernelGetProcessTimeWide(); 
}

void time_update()
{
	//sceRtcGetCurrentClockLocalTime(&dtime);
	
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
	//sceRtcGetCurrentClockLocalTime(&dtime);
	//return sceRtcGetSecond(&dtime) * 1000; 
	tnow = sceKernelGetProcessTimeWide(); 
	return (unsigned int) (tnow - tstart) / 1000; 
}

float time_delta_time()
{
	return delta_time; 
}

