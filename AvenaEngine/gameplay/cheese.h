#ifndef __CHEST_H__
#define __CHEST_H__

#include "../fm/obj.h"

#define MAX_CHEST 5

void cheese_init();
void cheese_start(); 
void cheese_update(); 
void cheese_player(vec4_t* pos, aabb_t* aabb, float* rotz); 
void cheese_set_placements(vec4_t placements, int amount);
obj_t* cheese_get_obj(); 

#endif/*__CHEST_H__*/
