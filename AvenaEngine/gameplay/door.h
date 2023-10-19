#ifndef __DOOR_H__
#define __DOOR_H__

#include "../fm/obj.h" 

#define MAX_DOORS 3

void doors_init();
void doors_start();
void doors_update(); 
void doors_get_player(); 
void doors_open(int i);
obj_t* doors_get_obj(int i);

#endif/*__DOOR_H__*/
