#ifndef __ACTRL_H__
#define __ACTRL_H__

#if defined(__PC__)
#include <SDL2/SDL.h>

#define BTN_START   0
#define BTN_A       1
#define PAD_UP      2//SDL_SCANCODE_W        
#define PAD_RIGHT   3//SDL_SCANCODE_D
#define PAD_DOWN    4//SDL_SCANCODE_S
#define PAD_LEFT    5//SDL_SCANCODE_A
#define D_UP        7//SDL_SCANCODE_UP
#define D_RIGHT     8//SDL_SCANCODE_RIGHT
#define D_DOWN      9//SDL_SCANCODE_DOWN
#define D_LEFT      10//SDL_SCANCODE_LEFT
#define BTN_B       11
#define BTN_X       0
#define BTN_Y       0
#endif 

#if defined(__DC__)
#define	BTN_A       (1<<2)
#define	BTN_B       (1<<1) 
#define	BTN_X       (1<<10)
#define	BTN_Y       (1<<9)
#define PAD_UP    	(1<<4)
#define PAD_DOWN  	(1<<5)
#define PAD_LEFT  	(1<<6)
#define PAD_RIGHT 	(1<<7) 
#define	BTN_START   (1<<3) 
#endif

#if defined(__PSP__)
#define	BTN_A       0x004000 /*CROSS*/
#define	BTN_B       0x002000 /*CIRCLE*/
#define	BTN_X   	0x008000 /*SQUARE*/
#define	BTN_Y   	0x001000 /*TRIANGLE*/	
#define PAD_UP    	0x000010 /*DPAD*/
#define PAD_DOWN  	0x000040
#define PAD_LEFT  	0x000080
#define PAD_RIGHT 	0x000020 /*DPAD*/
#define	BTN_START   0x010000 /*HOME*/
#endif 

#if defined(__PSV__)
#define	BTN_START   0x00000008
#define	PAD_UP      0x00000010
#define	PAD_RIGHT   0x00000020
#define	PAD_DOWN    0x00000040
#define	PAD_LEFT    0x00000080
#define	LTRIGGER    0x00000400
#define	RTRIGGER    0x00000800
#define	BTN_Y       0x00001000
#define	BTN_B       0x00002000
#define	BTN_A       0x00004000
#define	BTN_X       0x00008000
#endif 

void ctrl_init();
void ctrl_update();
int ctrl_event_quit(); 

float ctrl_x_axis(); //horizontal
float ctrl_y_axis(); //vertical 
int ctrl_button(int flag);
int ctrl_button_down(int flag);
//void ctrl_xaxis();
//void ctrl_yaxis();

#endif//__ACTRL_H__
