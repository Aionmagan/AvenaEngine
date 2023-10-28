#include "../ctrl.h"
#include "../timer.h"
//#include <SDL2/SDL.h>

#if defined(__WIN_P__)
#define JOYPORT_RAY 3
#define JOYPORT_RAX 2
#else 
#define JOYPORT_RAY 4
#define JOYPORT_RAX 3
#endif 

#define JOYDEADZONE 0.1

SDL_Joystick* gamepad = NULL; 
SDL_Event event; 
float x_axis = 0; 
float y_axis = 0; 
float x_raxis = 0; 
float y_raxis = 0; 

int is_joystick = 0;
int quit = 0; 
int keys[322];
int btns[24];
int skeys[322];
int sbtns[24];

/*INDEXER ARRAY*/
int gp_keys[]=
{
	6, //back button
	0, //A button
	7, //d-pad up
	8, //d-pad right
	9, //d-pad down 
	10, //d-pad left
	111, //useless
	111, //useless
	111, //useless
	111, //useless
	4, //useless
	1, //b button
	3, //x button 
	2, //y button
};

int pc_keys[14]=
{
	SDL_SCANCODE_ESCAPE,
	SDL_SCANCODE_SPACE,
	SDL_SCANCODE_W,        
	SDL_SCANCODE_D,
	SDL_SCANCODE_S,
	SDL_SCANCODE_A,
	SDL_SCANCODE_UP,
	SDL_SCANCODE_RIGHT,
	SDL_SCANCODE_DOWN,
	SDL_SCANCODE_LEFT,
	SDL_SCANCODE_LEFT,
	SDL_SCANCODE_LEFT,
	SDL_SCANCODE_SPACE,
	SDL_SCANCODE_RIGHT
}; 
/*INDEXER ARRAY*/

void ctrl_init()
{	
	SDL_SetRelativeMouseMode(1); 
	for(int i = 0; i < 322; ++i)
	{	
		keys[i] = 0; 
		skeys[i] = 0; 
	}
}

void ctrl_update()
{
	if (SDL_NumJoysticks() > 0)
	{
		//printf("checking joystick amount\n");
		if (gamepad == NULL)
		{
			//printf("collecting gamepad\n");
			for(int i = 0; i < SDL_NumJoysticks(); ++i)
			{
				gamepad = SDL_JoystickOpen(i); 
				
				if (gamepad != NULL) break; 
			}
		}
	}
	
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				quit = 1; 
				break; 
			case SDL_MOUSEMOTION: 
				is_joystick = 0;
				//x_raxis = ff_lerp(event.motion.xrel, 0, 0.3f);
				//x_raxis = ff_lerp(event.motion.yrel, 0, 0.3f); 
				x_raxis = event.motion.xrel*12*time_delta_time(); 
				y_raxis = event.motion.yrel*12*time_delta_time(); 
				//x_raxis = ff_lerp(x_raxis, 0, 0.3f);
				//y_raxis = ff_lerp(y_raxis, 0, 0.3f); 
				break; 
			case SDL_KEYDOWN: 
				is_joystick = 0; 
				if (event.key.repeat == 0)
					keys[event.key.keysym.scancode] = 1; 
					skeys[event.key.keysym.scancode] = 1; 
					if (event.key.keysym.scancode == SDL_SCANCODE_A)
						x_axis = -1.0f; 
					if (event.key.keysym.scancode == SDL_SCANCODE_D)
						x_axis = 1.0f; 
						
					if (event.key.keysym.scancode == SDL_SCANCODE_W)
						y_axis = -1.0f; 
					if (event.key.keysym.scancode == SDL_SCANCODE_S)
						y_axis = 1.0f; 
					
				break; 
			case SDL_KEYUP: 
				is_joystick = 0; 
					keys[event.key.keysym.scancode] = 0;
					skeys[event.key.keysym.scancode] = 0; 
					if (event.key.keysym.scancode == SDL_SCANCODE_A && x_axis < 0.0f)
						x_axis = 0; 
					if (event.key.keysym.scancode == SDL_SCANCODE_D && x_axis > 0.0f)
						x_axis = 0; 
						
					if (event.key.keysym.scancode == SDL_SCANCODE_W && y_axis < 0.0f)
						y_axis = 0; 
					if (event.key.keysym.scancode == SDL_SCANCODE_S && y_axis > 0.0f)
						y_axis = 0; 
				break;
				
			case SDL_JOYBUTTONDOWN: 
				is_joystick = 1; 
					//printf("Joy Button Pressed %d\n", event.jbutton.button); 

					if (event.jbutton.button < 7)
					{
						btns[event.jbutton.button] = 1;
						sbtns[event.jbutton.button] = 1; 
					}
				break; 
			case SDL_JOYBUTTONUP: 
				is_joystick = 1; 
					//printf("Joy Button Pressed %d\n", event.jbutton.button); 
					
					if (event.jbutton.button < 7)
					{
						btns[event.jbutton.button] = 0; 
						sbtns[event.jbutton.button] = 0; 
					}
				break; 
			case SDL_JOYDEVICEADDED:
			case SDL_JOYDEVICEREMOVED: 
					printf("Device updated\n");
				break;
				
			case SDL_JOYAXISMOTION:
				is_joystick = 1;
			  		if( event.jaxis.which == 0 )
              		{                        
                		if( event.jaxis.axis == 0 )
                		{
							//printf("Jaxis X = %f\n", event.jaxis.value/32767.0f);
							x_axis = event.jaxis.value/32767.0f; 
						}
						
						if( event.jaxis.axis == 1)
						{
							//printf("Jaxis Y = %f\n", event.jaxis.value/32767.0f);
							y_axis = event.jaxis.value/32767.0f; 
						}
						
						if( event.jaxis.axis == JOYPORT_RAX )
                		{
							//printf("Jaxis X = %f\n", event.jaxis.value/32767.0f);
							x_raxis = event.jaxis.value/32767.0f; 
						}
						
						if( event.jaxis.axis == JOYPORT_RAY)
						{
							//printf("Jaxis Y = %f\n", event.jaxis.value/32767.0f);
							y_raxis = event.jaxis.value/32767.0f; 
						}
						/*
						for(int i = 0; i < 16; ++i)
						{
							if (event.jaxis.axis == i)
								printf("event.jaxis.axis = %d | %d\n", i, event.jaxis.value);
						}
						*/
					}
				break;
			case SDL_JOYHATMOTION:
				is_joystick = 1; 
					if (event.jhat.which == 0)
					{
						if (event.jhat.hat == 0)
						{
							switch(event.jhat.value)
							{
								case 1:
									btns[7] = 1;
									break;
								case 2:
									btns[8] = 1; 
									break;
								case 4:
									btns[9] = 1; 
									break;
								case 8:
									btns[10]= 1; 
									break;
								default:break; 
							} 
						}
					}
				
			default:break; 
		}
	}
}

int ctrl_event_quit()
{
	return quit;  
}

float ctrl_x_laxis()
{
	x_axis = (fabs(x_axis) < JOYDEADZONE) ? 0 : x_axis; 
	return x_axis; 
}

float ctrl_y_laxis()
{
	y_axis = (fabs(y_axis) < JOYDEADZONE) ? 0 : y_axis; 
	return y_axis; 
}

float ctrl_x_raxis()
{
	float x = x_raxis; 
	if (is_joystick)
		x_raxis = (fabs(x_raxis) < JOYDEADZONE) ? 0 : x_raxis; 
	else
		x_raxis = 0;
		  
	return x; 
}

float ctrl_y_raxis()
{
	float y = y_raxis; 
	if (is_joystick)
		y = (fabs(y_raxis) < JOYDEADZONE) ? 0 : y_raxis;  
	else 
		y_raxis = 0;
		
	return y; 
}

int ctrl_button(int flag)
{
	if (sbtns[gp_keys[flag]])return 1;
	if (skeys[pc_keys[flag]])return 1;
}

int ctrl_button_down(int flag)
{
	
	if (btns[gp_keys[flag]])
	{
		btns[gp_keys[flag]] = 0; 
		return 1; 
	}
	if (keys[pc_keys[flag]])
	{
		keys[pc_keys[flag]] = 0; 
		return 1; 
	}
	
	return 0; 
}
