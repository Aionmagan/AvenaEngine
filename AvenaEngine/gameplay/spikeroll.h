#ifndef __SPIKEROLL_H__
#define __SPIKEROLL_H__

#define MAX_SPIKEROLL 4
#include "../fm/obj.h"

void spikeroll_init();
void spikeroll_start(); 
void spikeroll_update(); 
void spikeroll_player(aabb_t* aabb);
obj_t* spikeroll_get_obj(int i); 

#endif/*__SPIKEROLL_H__*/
