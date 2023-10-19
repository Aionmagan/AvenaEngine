#include "switch.h"

#include "../fw.h"
#include "../fm/timer.h"
#include "../fm/obj.h" 

#include "player.h"
#include "door.h"

mesh_t switch_mesh; 
tex_t switch_tex;
tex_t switch_tex1;  

obj_t switchs[MAX_SWITCHS];

vec4_t switch_box_pos[MAX_SWITCHS];
vec4_t switch_box_sca;

int switch_enabled = 0; 

aabb_t* player_box_switch;

void switchs_init()
{
	load_mesh("Assets/switch.obj", &switch_mesh); 
	load_png_texture("Assets/switch.png", &switch_tex);
	load_png_texture("Assets/switch1.png", &switch_tex1);
	
	switch_box_pos[0].x =  98.0f;
	switch_box_pos[0].y =  10.0f;
	switch_box_pos[0].z =  380.0f;
	
	switch_box_pos[1].x = -75.0f;
	switch_box_pos[1].y =  10.0f;
	switch_box_pos[1].z =  228.0f;
	
	switch_box_pos[2].x = -180.0f;
	switch_box_pos[2].y =  10.0f;
	switch_box_pos[2].z =  125.0f;
	
	switch_box_pos[3].x =  75.0f;
	switch_box_pos[3].y =  10.0f;
	switch_box_pos[3].z = -175.0f;
	
	switch_box_pos[4].x =  -2.0f;
	switch_box_pos[4].y =  115.0f;
	switch_box_pos[4].z =  12.0f;
	
	switch_box_pos[5].x = 75.0f;
	switch_box_pos[5].y = 10.0f;
	switch_box_pos[5].z = 525.0f;
	
	switch_box_sca.x = 10.0f;
	switch_box_sca.y = 10.0f;
	switch_box_sca.z = 10.0f; 
	
	for (int i = 0; i < MAX_SWITCHS; ++i)
	{	
		obj_init(&switchs[i]);
		
		switchs[i].model = &switch_mesh;
		switchs[i].texture = switch_tex; 
		switchs[i].pos = switch_box_pos[i];
		
		aabb_init(&switchs[i].box, &switchs[i].pos, &switch_box_sca);
	}
	
	switchs[0].rot.y = 90.0f;
	switchs[1].rot.y = 180.0f;
	switchs[2].rot.y = 0.0f;
	switchs[3].rot.y = 0.0f;
	switchs[4].rot.y = 90.0f;
	switchs[5].rot.y = 0.0f;
	
	player_box_switch = player_get_aabb();
}

void switchs_start()
{
	for (int i = 0; i < MAX_SWITCHS; ++i)
	{
		switchs[i].rot.z = 0; 
		switchs[i].pos.y = switch_box_pos[i].y;
		switchs[i].texture = switch_tex; 
		switchs[i].box.is_active = 1; 
	}
	
	switch_enabled = 0; 
}

void switchs_update()
{
	for (int i = 0; i < MAX_SWITCHS; ++i)
	{
		aabb_update(&switchs[i].box, &switch_box_pos[i], &switch_box_sca);


#if defined(__DEBUG__)		
		aabb_hit(&switchs[i].box, player_box_switch);
#endif

		if (ctrl_button(BTN_A))
		{
			if (aabb_overlap(player_box_switch, &switchs[i].box))
			{
				switchs[i].box.is_active = 0; 
				switch_enabled ++; 
				switchs[i].rot.z = 180.0f;
				switchs[i].pos.y += 15.0f;
				switchs[i].texture = switch_tex1;
				
				audio_play_sfx(0);
				
				if (switch_enabled == 2)
					player_lookat_door(0);
	
				if (switch_enabled == 5)
					player_lookat_door(1);
					
				if (switch_enabled == 6)
					player_lookat_door(2);
			}
		}		
	}

	if (switch_enabled > 1)
		doors_open(0); 
	
	if (switch_enabled > 4)
		doors_open(1);
		
	if (switch_enabled > 5)
		doors_open(2);
} 

obj_t* switchs_get_obj(int i)
{
	return &switchs[i];
}
