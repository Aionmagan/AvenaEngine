#include "chest.h"
#include "../fm/pngloader.h"
#include "../fw.h"

obj_t chest; 
mesh_t chest_model; 
vec4_t* chest_player_pos; 
float* chest_player_rot_z; 
aabb_t* chest_player_box; 
 
int is_taken = 0;

void chest_init()
{
	load_mesh("Assets/chest.obj", &chest_model);
	load_png_texture("Assets/chest.png", &chest.texture);  
	obj_init(&chest);
	chest.model = &chest_model;
	chest.pos.x = 12.0f;
	chest.pos.z = -15.0f;
	chest.pos.y = 0.4f; 
	chest.sca.z = 0.2f; 
	chest.sca.y = 0.2f; 
	chest.sca.x = 0.2f; 
	
	aabb_update(&chest.box, &chest.pos, &chest.sca); 
}

void chest_start()
{
	is_taken = 0; 
	chest.pos.x = 12.0f;
	chest.pos.z = -15.0f;
	chest.pos.y = 0.4f; 
}
 
void chest_update()
{

	if (is_taken)
	{
		chest.pos.x = chest_player_pos->x; 
		chest.pos.y = chest_player_pos->y + 0.8f; 
		chest.pos.z = chest_player_pos->z; 
		chest.rot.y = *chest_player_rot_z; 
	}else
	{
		if (ctrl_button_down(BTN_X))
		{
			if (aabb_overlap(&chest.box, chest_player_box))
			{
				is_taken = 1; 
			}
		}
	}
}

void chest_player(vec4_t* pos, aabb_t* aabb, float* rotz)
{
	chest_player_pos = pos; 
	chest_player_box = aabb;
	chest_player_rot_z = rotz;
}

obj_t* chest_get_obj()
{
	return &chest; 
}

