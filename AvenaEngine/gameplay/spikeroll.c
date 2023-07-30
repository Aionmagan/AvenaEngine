#include "spikeroll.h"
#include "../fm/pngloader.h"
#include "../fw.h" 

obj_t spikerolls[MAX_SPIKEROLL];
mesh_t spikeroll_model; 
tex_t spikeroll_tex;
vec4_t spikeroll_sca; /*for collision*/
aabb_t* spikeroll_player_box; 
int spki; 

void spikeroll_init()
{
	load_mesh("Assets/spikerollt.obj", &spikeroll_model); 
	load_png_texture("Assets/spikerollt.png", &spikeroll_tex);
	
	spikeroll_sca.x = 0.5f;
	spikeroll_sca.y = 0.5f; 
	spikeroll_sca.z = 4.8f; 
	
	for(int i = 0; i < MAX_SPIKEROLL; ++i)
	{
		obj_init(&spikerolls[i]);
		spikerolls[i].model = &spikeroll_model; 
		spikerolls[i].texture = spikeroll_tex; 
		spikerolls[i].pos.z = -20.0f;
		spikerolls[i].pos.y = 0.8f; 
		spikerolls[i].pos.x = 1.0f*-(i*4);
		spikerolls[i].sca.x = 0.5f;
		spikerolls[i].sca.y = 0.5f;
		spikerolls[i].sca.z = 0.5f;
		 
	} 
	
}

void spikeroll_start()
{

}
 
void spikeroll_update()
{
	for(int spki = 0; spki < MAX_SPIKEROLL; ++spki)
	{
		spikerolls[spki].rot.z += 150.0f * time_delta_time();
		aabb_update(&spikerolls[spki].box, &spikerolls[spki].pos, &spikeroll_sca);
		
		aabb_hit(&spikerolls[spki].box, spikeroll_player_box); 
	}
}

void spikeroll_player(aabb_t* aabb)
{
	spikeroll_player_box = aabb; 
}
 
obj_t* spikeroll_get_obj(int i)
{
	return &spikerolls[i];
} 
