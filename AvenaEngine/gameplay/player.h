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
int player_get_lvl();

void player_push_back(vec4_t push);
void player_lookat_door(int i);

aabb_t* player_get_aabb();
vec4_t* player_get_pos(); 

#endif//__PLAYER_H__
