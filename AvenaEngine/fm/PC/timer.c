#include "../timer.h"
#include <SDL2/SDL.h>

float delta_time = 0; 
unsigned int new_time, old_time; 

void time_init()
{
	srand(time(NULL));
}

void time_update()
{
	old_time = new_time; 
	new_time = time_get_tick(); 
	delta_time = (new_time - old_time)*0.001f; 
}

unsigned long time_get_tick()
{
	return (unsigned long) SDL_GetTicks(); 
}

float time_delta_time()
{
	return delta_time; 
}
