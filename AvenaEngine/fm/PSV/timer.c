#include "../timer.h"
#include <psp2/rtc.h>

//SceDateTime dtime; 

uint64_t start, now; 
void time_init()
{
	start = sceKernelGetProcessTimeWide(); 
}

void time_update()
{
	//sceRtcGetCurrentClockLocalTime(&dtime);
}

unsigned long time_get_tick()
{
	//sceRtcGetCurrentClockLocalTime(&dtime);
	//return sceRtcGetSecond(&dtime) * 1000; 
	now = sceKernelGetProcessTimeWide(); 
	return (unsigned int) (now - start) / 1000; 
}

