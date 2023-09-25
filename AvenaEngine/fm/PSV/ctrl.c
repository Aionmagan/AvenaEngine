#include "../ctrl.h"
//#include <SDL2/SDL.h>
#include <psp2/ctrl.h>
#include <math.h>
#include <stdlib.h>

#define JOYDEADZONE 32

SceCtrlData pad; 
int last_state = 0; 
int is_down = 0; 
float x_axis; 
float y_axis; 
float x_raxis; 
float y_raxis; 

void ctrl_init()
{	
	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
}

void ctrl_update()
{
	sceCtrlReadBufferPositive(0, &pad, 1);
	is_down = pad.buttons & (pad.buttons ^ last_state);
	last_state = pad.buttons; 
}

int ctrl_event_quit()
{
	return 0;
}

float ctrl_x_laxis()
{
	int p = pad.lx-128; 
	x_axis = (abs(p) < JOYDEADZONE) ? 0 : p/128.0f; 
	return x_axis; 
}

float ctrl_y_laxis()
{
	int p = pad.ly-128; 
	y_axis = (abs(p) < JOYDEADZONE) ? 0 : p/128.0f; 
	return y_axis; 
}

float ctrl_x_raxis()
{
	int p = pad.rx-128; 
	x_raxis = (abs(p) < JOYDEADZONE) ? 0 : p/128.0f; 
	return x_raxis; 
}

float ctrl_y_raxis()
{
	int p = pad.ry-128; 
	y_raxis = (abs(p) < JOYDEADZONE) ? 0 : p/128.0f; 
	return y_raxis; 
}

int ctrl_button(int flag)
{
	return pad.buttons & flag;
}

int ctrl_button_down(int flag)
{
	
	return is_down & flag; 
}
