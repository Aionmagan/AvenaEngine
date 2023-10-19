#include "modes.h" 
int modes; 
int start_call = 0; 

void mode_init()
{
	modes = MODE_GAMEPLAY;
	//modes = MODE_MAINMENU; 
	//modes = MODE_SELECTSCRN; 
} 
void mode_change(int flag)
{
	modes = flag; 
	start_call = 1; 
} 

int mode_one_call()
{
	if (start_call)
	{
		start_call = 0; 
		return 1;
	}
	return 0; 
}

int mode_get()
{
	return modes; 
} 
