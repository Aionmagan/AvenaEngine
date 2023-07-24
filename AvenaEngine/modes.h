#ifndef __MODES_H__
#define __MODES_H__

#define MODE_MAINMENU 0 
#define MODE_SELECTSCRN 1
#define MODE_GAMEPLAY 2

void mode_init(); 
void mode_change(int flag); 
int mode_one_call(); 
int mode_get(); 

#endif//__MODES_H__
