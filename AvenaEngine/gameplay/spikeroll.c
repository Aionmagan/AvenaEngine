#include "spikeroll.h"
#include "../fm/pngloader.h"
#include "../fw.h" 
#include <math.h>

obj_t spikerolls[MAX_SPIKEROLL];
mesh_t spikeroll_model; 
tex_t spikeroll_tex;
vec4_t spikeroll_sca; /*for collision*/
aabb_t* spikeroll_player_box; 
int spki; 

/*position / rotation / scale / aabb*/ 
vec4_t placements[]=
{
	/*chest 0*/
	{.x=-17.0f, .y=-1.8f, .z=-20.0f},/*pos*/
	{.x= 90.0f, .y= 0.0f, .z= 0.0f},/*rot*/
	{.x= 0.5f, .y= 0.5f, .z= 0.5f},/*sca*/
	{.x= 0.5f, .y= 5.5f, .z= 0.5f},/*sca*/
	/*chest 0*/
	
	/*chest 1*/
	{.x=-6.0f, .y=0.4f, .z=-11.0f},/*pos*/
	{.x= 0.0f, .y= 0.0f, .z= 0.0f},/*rot*/
	{.x= 0.5f, .y= 0.5f, .z= 0.5f},/*sca*/
	{.x= 0.5f, .y= 0.5f, .z= 5.2f},/*sca*/
	
	{.x=-4.3f, .y=0.4f, .z=-15.0f},/*pos*/
	{.x= 0.0f, .y= 90.0f, .z= 0.0f},/*rot*/
	{.x= 0.12f, .y= 0.5f, .z= 0.5f},/*sca*/
	{.x= 1.5f, .y= 0.5f, .z= 0.5f},/*sca*/
	
	{.x=-3.0f, .y=0.4f, .z=-16.0f},/*pos*/
	{.x= 0.0f, .y= 0.0f, .z= 0.0f},/*rot*/
	{.x= 0.5f, .y= 0.5f, .z= 0.5f},/*sca*/
	{.x= 0.5f, .y= 0.5f, .z= 5.5f},/*sca*/
	/*chest 1*/ 
	
	/*chest 2*/
	{.x= 5.0f, .y=0.4f, .z=-18.0f},/*pos*/   // /  	h1
	{.x= 0.0f, .y= 90.0f, .z= 0.0f},/*rot*/
	{.x= 0.1f, .y= 0.5f, .z= 0.5f},/*sca*/
	{.x= 0.8f, .y= 0.5f, .z= 0.5f},/*sca*/
	
	{.x= 3.7f, .y=0.3f, .z=-16.0f},/*pos*/   // //  v1
	{.x= 0.0f, .y= 0.0f, .z= 0.0f},/*rot*/
	{.x= 0.5f, .y= 0.5f, .z= 0.2f},/*sca*/
	{.x= 0.5f, .y= 0.5f, .z= 1.7f},/*sca*/
	
	{.x= 5.0f, .y=0.4f, .z=-14.0f},/*pos*/   // ///  h2
	{.x= 0.0f, .y= 90.0f, .z= 0.0f},/*rot*/
	{.x= 0.1f, .y= 0.5f, .z= 0.5f},/*sca*/
	{.x= 0.8f, .y= 0.5f, .z= 0.5f},/*sca*/
	
	{.x= 6.0f, .y=0.3f, .z=-16.0f},/*pos*/   //      v2
	{.x= 0.0f, .y= 0.0f, .z= 0.0f},/*rot*/
	{.x= 0.5f, .y= 0.5f, .z= 0.2f},/*sca*/
	{.x= 0.5f, .y= 0.5f, .z= 1.7f},/*sca*/
	/*chest 2*/
	
	/*chest 3*/
	{.x= 15.0f, .y=0.4f, .z=-14.0f},/*pos*/
	{.x= 90.0f, .y= 0.0f, .z= 0.0f},/*rot*/		//
	{.x= 0.5f, .y= 0.1f, .z= 0.5f},/*sca*/
	{.x= 0.5f, .y= 1.0f, .z= 0.5f},/*sca*/
	
	{.x= 17.3f, .y=0.5f, .z=-17.0f},/*pos*/
	{.x= 90.0f, .y= 0.0f, .z= 0.0f},/*rot*/
	{.x= 0.5f, .y= 0.1f, .z= 0.5f},/*sca*/
	{.x= 0.5f, .y= 1.0f, .z= 0.5f},/*sca*/
	/*chest 3*/
	
	/*chest 4*/
	{.x= 25.0f, .y=0.4f, .z=-19.0f},/*pos*/
	{.x= 0.0f, .y= 0.0f, .z= 0.0f},/*rot*/
	{.x= 0.5f, .y= 0.5f, .z= 0.5f},/*sca*/
	{.x= 0.5f, .y= 0.5f, .z= 2.5f},/*sca*/
	
	{.x= 27.0f, .y=0.4f, .z=-19.0f},/*pos*/
	{.x= 0.0f, .y= 0.0f, .z= 0.0f},/*rot*/
	{.x= 0.5f, .y= 0.5f, .z= 0.5f},/*sca*/
	{.x= 0.5f, .y= 0.5f, .z= 2.5f},/*sca*/
	
	{.x= 25.0f, .y=1.4f, .z=-19.0f},/*pos*/
	{.x= 0.0f, .y= 0.0f, .z= 0.0f},/*rot*/
	{.x= 0.5f, .y= 0.5f, .z= 0.5f},/*sca*/
	{.x= 0.5f, .y= 0.5f, .z= 2.5f},/*sca*/
	
	{.x= 27.0f, .y=1.4f, .z=-19.0f},/*pos*/
	{.x= 0.0f, .y= 0.0f, .z= 0.0f},/*rot*/
	{.x= 0.5f, .y= 0.5f, .z= 0.5f},/*sca*/
	{.x= 0.5f, .y= 0.5f, .z= 2.5f},/*sca*/
	/*chest 4*/
};

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
		
		spikerolls[i].pos = placements[0+(4*i)];
		spikerolls[i].rot = placements[1+(4*i)];
		spikerolls[i].sca = placements[2+(4*i)];
		//spikerolls[i].pos.z = -20.0f;
		//spikerolls[i].pos.y = 0.8f; 
		//spikerolls[i].pos.x = 1.0f*-(i*2);
		//spikerolls[i].sca.x = 0.5f;
		//spikerolls[i].sca.y = 0.5f;
		//spikerolls[i].sca.z = 0.5f;
		 
	} 
	
}

void spikeroll_start()
{

}
 
void spikeroll_update()
{
	/*chest 0 logic*/
	spikerolls[0].pos.x = placements[0].x+sinf(time_get_tick()*0.003f)-2.0f;
	spikerolls[0].pos.z = placements[0].z+fabsf(cosf(time_get_tick()*0.003f));
	/*chest 0 logic*/

	
	/*chest 3 logic*/
	spikerolls[8].pos.x = placements[32].x+1.0f+(1.4f*sinf(time_get_tick()*0.005f));
	spikerolls[8].pos.z = placements[32].z-1.0f+(1.4f*cosf(time_get_tick()*0.005f));
	
	spikerolls[9].pos.x = placements[36].x-1.0f-(1.4f*sinf(time_get_tick()*0.005f));
	spikerolls[9].pos.z = placements[36].z+1.7f-(1.4f*cosf(time_get_tick()*0.005f));
	/*chest 3 logic*/
	 
	//printf("spikerolls = {%f, %f} | placements = {%f, %f}\n", spikerolls[0].pos.x, spikerolls[0].pos.z, placements[0].x, placements[0].z);
	for(int spki = 0; spki < MAX_SPIKEROLL; ++spki)
	{
		spikerolls[spki].rot.z += 150.0f * time_delta_time();
		aabb_update(&spikerolls[spki].box, &spikerolls[spki].pos, &placements[3+(4*spki)]);
		
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
