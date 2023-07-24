#include "../ctrl.h"
#include <pspctrl.h>

#define JOYDEADZONE 16 

SceCtrlData pad;

float x_axis = 0; 
float y_axis = 0; 

int last_state = 0; 
int is_down = 0; 

void ctrl_init()
{	
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(1);
}

void ctrl_update()
{
	sceCtrlReadBufferPositive(&pad, 1);
	
	is_down = pad.Buttons & (pad.Buttons ^ last_state); 
	last_state = pad.Buttons;  
}

int ctrl_event_quit()
{
	return 0; 
}

float ctrl_x_axis()
{
	int p = pad.Lx-128; 
	x_axis = (abs(p) < JOYDEADZONE) ? 0 : p/128.0f; 
	return x_axis; 
}

float ctrl_y_axis()
{
	int p = pad.Ly-128; 
	y_axis = (abs(p) < JOYDEADZONE) ? 0 : p/128.0f; 
	return y_axis; 
}

int ctrl_button(int flag)
{
	return pad.Buttons & flag; 
}

int ctrl_button_down(int flag)
{	
	return is_down & flag; 
}
