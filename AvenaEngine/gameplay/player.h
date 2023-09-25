#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../fm/obj.h"
#include "../fm/pngloader.h" 

#define MAX_CH 5

void player_init();
void player_start(); 
void player_update(); 
int player_is_alive();
//objmd2_t* player_get_obj();
void player_reset(); 
 
obj_t* player_get_obj(); 
objmd2_t* player_get_objmd2(); 
#endif//__PLAYER_H__
