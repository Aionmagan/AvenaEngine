#ifndef __CHEST_H__
#define __CHEST_H__

#include "../fm/obj.h"

#define MAX_CHEST 5

void chest_init();
void chest_start(); 
void chest_update(); 
void chest_player(vec4_t* pos, aabb_t* aabb, float* rotz); 
obj_t* chest_get_obj(int i); 

#endif/*__CHEST_H__*/
