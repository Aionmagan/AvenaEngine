#include "../ctrl.h"
#include <math.h>
#include <stdlib.h>
#include <dc/maple.h>
#include <dc/maple/controller.h>
//#include <SDL2/SDL.h>

#define JOYDEADZONE 32

cont_state_t* state = NULL; 
int is_down = 0; 
int last_state = 0; 
float x_axis = 0.0f; 
float y_axis = 0.0f; 

void ctrl_init()
{

}

void ctrl_update()
{
	state = (cont_state_t *)maple_dev_status(maple_enum_type(0, MAPLE_FUNC_CONTROLLER));
	
	is_down = state->buttons & (state->buttons ^ last_state);
	last_state = state->buttons; 
	
	//printf("state = %x | last_state %x\n", state->buttons, last_state);
}

int ctrl_event_quit()
{
	return 0;  
}

float ctrl_x_laxis()
{
	//printf("joyx %d\n", state->joyx);
	x_axis = (abs(state->joyx) < JOYDEADZONE) ? 0 : state->joyx/128.0f; 
	return x_axis; 
}

float ctrl_y_laxis()
{
	//printf("joyy %d\n", state->joyy);
	y_axis = (abs(state->joyy) < JOYDEADZONE) ? 0 : state->joyy/128.0f; 
	return y_axis; 
}

float ctrl_x_raxis()
{
	return 0;
}
 
float ctrl_y_raxis()
{
	return 0; 
}

int ctrl_button(int flag)
{
	return state->buttons & flag;
}

int ctrl_button_down(int flag)
{
	//return ctrl_button(flag); 
	//printf("is_down & flag = %x\n", is_down & flag);
	return is_down & flag;  
}
