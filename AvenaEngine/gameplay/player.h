#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../fm/obj.h"
#include "../fm/pngloader.h" 

#define MAX_CH 5

void player_init();
void player_start(); 
void player_update(); 
objmd2_t* player_get_obj(); 
#endif//__PLAYER_H__
