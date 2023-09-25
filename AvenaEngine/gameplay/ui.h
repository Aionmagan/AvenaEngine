#ifndef __AUI_H__
#define __AUI_H__

#include "../fm/obj.h"
#define MAX_CHEESES 5

void ui_init(); 
void ui_start(); 
void ui_update(); 
void ui_cheese_taken();
void ui_cheese_reset(); 
obj_t* ui_cheese_render(int i);
	
#endif
