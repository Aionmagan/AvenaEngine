#ifndef __CHEST_H__
#define __CHEST_H__

#include "../fm/obj.h"

void chest_init();
void chest_start(); 
void chest_update(); 
void chest_player(vec4_t* pos, aabb_t* aabb); 
obj_t* chest_get_obj(); 

#endif/*__CHEST_H__*/
