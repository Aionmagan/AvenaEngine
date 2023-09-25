#ifndef __SPIKEROLL_H__
#define __SPIKEROLL_H__

#define MAX_CATS 5
#include "../fm/obj.h"

void cats_init();
void cats_start(); 
void cats_update(); 
void cats_player(aabb_t* aabb);
vec4_t cats_get_placements(); 
obj_t* cats_get_obj(int i); 
obj_t* cat_get_obj(); 
vec4_t* get_placements(); 
#endif/*__SPIKEROLL_H__*/
