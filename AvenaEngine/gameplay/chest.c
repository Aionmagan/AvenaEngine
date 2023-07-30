#include "chest.h"
#include "../fm/pngloader.h"
#include "../fw.h"

obj_t chest[MAX_CHEST]; 
mesh_t chest_model; 
tex_t chest_texture; 
vec4_t chest_positions[MAX_CHEST]=
{
	//{.x=12.0f, .y=0.4f, .z=-15.0f},
	//{.x=10.0f, .y=0.4f, .z=-15.0f},
	//{.x=8.0f, .y=0.4f, .z=-15.0f},
	//{.x=6.0f, .y=0.4f, .z=-15.0f},
	{.x=4.0f, .y=0.4f, .z=-15.0f},
	{.x=6.0f, .y=0.4f, .z=-15.0f},
	{.x=8.0f, .y=0.4f, .z=-15.0f},
	{.x=10.0f, .y=0.4f, .z=-15.0f},
	{.x=12.0f, .y=0.4f, .z=-15.0f},
};

vec4_t* chest_player_pos; 
float* chest_player_rot_z; 
aabb_t* chest_player_box; 
 
int is_taken[MAX_CHEST] = {0};

void chest_init()
{
	load_mesh("Assets/chest.obj", &chest_model);
	load_png_texture("Assets/chest.png", &chest_texture);  
	
	for(int i = 0; i < MAX_CHEST; ++i)
	{
		obj_init(&chest[i]);
		chest[i].model = &chest_model;
		chest[i].texture = chest_texture;
		//chest[i].pos.x = 12.0f;
		//chest[i].pos.z = -15.0f;
		//chest[i].pos.y = 0.4f; 
		chest[i].pos = chest_positions[i];
		chest[i].sca.z = 0.2f; 
		chest[i].sca.y = 0.2f; 
		chest[i].sca.x = 0.2f; 
		is_taken[i] = 0; 
		aabb_update(&chest[i].box, &chest[i].pos, &chest[i].sca); 
	}
}

void chest_start()
{
	for(int i = 0; i < MAX_CHEST; ++i)
	{
		is_taken[i] = 0; 
		chest[i].pos.x = 12.0f;
		chest[i].pos.z = -15.0f;
		chest[i].pos.y = 0.4f; 
	}
}
 
void chest_update()
{

	for(int i = 0; i < MAX_CHEST; ++i)
	{
	//aabb_update(&chest[i].box, &chest[i].pos, &chest[i].sca);
		if (is_taken[i])
		{
			chest[i].pos.x = chest_player_pos->x; 
			chest[i].pos.y = chest_player_pos->y + 0.8f; 
			chest[i].pos.z = chest_player_pos->z; 
			chest[i].rot.y = *chest_player_rot_z; 
		}else
		{
			if (ctrl_button_down(BTN_X))
			{
				if (aabb_overlap(&chest[i].box, chest_player_box))
				{
					is_taken[i] = 1; 
					printf("Takes\n");		
				}
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

obj_t* chest_get_obj(int i)
{
	return &chest[i]; 
}

