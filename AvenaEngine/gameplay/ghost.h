#ifndef __GHOST_H__
#define __GHOST_H__

#include "../fm/obj.h"

#define MAX_GHOSTS 3

void ghosts_init();
void ghosts_start(); 
void ghosts_update(); 

void ghosts_reset(); 

obj_t* ghosts_get_obj(int i); 

#endif/*__GHOST_H__*/
