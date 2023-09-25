#include "cheese.h"
#include "ui.h"
#include "player.h"
#include "cats.h"
#include "../fm/pngloader.h"
#include "../fw.h"
#include "ui.h"

obj_t cheese; 
mesh_t cheese_model; 
tex_t cheese_texture; 

vec4_t* chest_player_pos; 
float* chest_player_rot_z; 
aabb_t* chest_player_box; 
 
vec4_t cats_placements; 
int amount_placements; 

void cheese_init()
{
	load_mesh("Assets/cheese.obj", &cheese_model);
	load_png_texture("Assets/cheese.png", &cheese.texture);  
	
	obj_init(&cheese);
	cheese.model = &cheese_model; 
	cheese.box.is_active = 1;
 
	cheese.pos.y = 12.0f; 
	cheese.sca.x = 4.0f;
	cheese.sca.y = 4.0f;
	cheese.sca.z = 4.0f;
	
	//cheese.pos = cats_placements[rand()%amount_placements-1];
	cheese.pos = cats_get_placements(); 
}

void cheese_start()
{

	
}
 
void cheese_update()
{

	cheese.rot.y += 0.6f; 
	aabb_update(&cheese.box, &cheese.pos, &cheese.sca);
	
	if (aabb_overlap(&cheese.box, &player_get_objmd2()->box)) 
	{
		printf("hit \n");
		cheese.pos = cats_get_placements(); 
		ui_cheese_taken();
	}
}

void cheese_player(vec4_t* pos, aabb_t* aabb, float* rotz)
{
	chest_player_pos = pos; 
	chest_player_box = aabb;
	chest_player_rot_z = rotz;
}

void cheese_set_placements(vec4_t placements, int amount)
{
	//cats_placements = placements; 
	//amount_placements = amount; 
	cheese.pos = placements;
}

obj_t* cheese_get_obj()
{
	return &cheese; 
}

