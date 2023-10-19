#ifndef __SWITCH_H__
#define __SWITCH_H__

#include "../fm/obj.h"

#define MAX_SWITCHS 6

void switchs_init();
void switchs_start();
void switchs_update(); 

obj_t* switchs_get_obj(int i);

#endif/*__SWITCH_H__*/
