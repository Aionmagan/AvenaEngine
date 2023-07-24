#include "../timer.h"
#include <time.h>
#include <sys/time.h>

struct timeval start, now; 

void time_init()
{
	gettimeofday(&start, NULL);
}

void time_update()
{

}

unsigned long time_get_tick()
{
	gettimeofday(&now, NULL); 
	return (unsigned int) ((now.tv_sec - start.tv_sec)*1000)+((now.tv_usec - start.tv_usec)/1000);
}

