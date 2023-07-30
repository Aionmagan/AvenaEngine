#ifndef __AUI_H__
#define __AUI_H__

#include "../fm/obj.h"
#define MAX_HEARTS 3
#define MAX_CHESTS 5

void ui_init(); 
void ui_start(); 
void ui_update(); 
obj_t* ui_hearts_render(int i);
obj_t* ui_chests_render(int j);
	
#endif
