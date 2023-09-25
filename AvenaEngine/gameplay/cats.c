#include "cats.h"
#include "player.h"
#include "../fm/pngloader.h"
#include "../fw.h" 
#include <math.h>

#define CATS_SPEED 15.1

//obj_t cat; 
obj_t cats[MAX_CATS];
mesh_t cat_model; 
tex_t cat_tex;
//vec4_t spikeroll_sca; /*for collision*/
aabb_t* cat_player_box; 
int spki; 
int rand_cat_select[MAX_CATS];
int last_returned_placement = 0;

vec4_t last_node[MAX_CATS];
vec4_t current_node[MAX_CATS]; 
vec4_t forward_vec = {0.0f, 0.0f, 1.0f}; //blender being trash
/*position*/ 
vec4_t placements[]=
{
	/*node 0*/
	{.x=-100.0f, .y= 3.0f, .z=-100.0f},
	
	/*node 1*/
	{.x=-33.0f,  .y= 3.0f, .z=-100.0f},
	
	/*node 2*/
	{.x= 33.0f,  .y= 3.0f, .z=-100.0f},   
	
	/*node 3*/
	{.x= 100.0f, .y= 3.0f, .z=-100.0f},
	
	/*node 4*/
	{.x=-100.0f, .y= 3.0f, .z=-33.0f},
	
	/*node 5*/
	{.x=-33.0f,  .y= 3.0f, .z=-33.0f},
	
	/*node 6*/
	{.x= 33.0f,  .y= 3.0f, .z=-33.0f},
	
	/*node 7*/
	{.x= 100.0f, .y= 3.0f, .z=-33.0f},
	
	/*node 8*/
	{.x=-100.0f, .y= 3.0f, .z= 33.0f},
	
	/*node 9*/
	{.x=-33.0f,  .y= 3.0f, .z= 33.0f},
	
	/*node 10*/
	{.x= 33.0f,  .y= 3.0f, .z= 33.0f},   
	
	/*node 11*/
	{.x= 100.0f, .y= 3.0f, .z= 33.0f},
	
	/*node 12*/
	{.x=-100.0f, .y= 3.0f, .z= 100.0f},
	
	/*node 13*/
	{.x=-33.0f,  .y= 3.0f, .z= 100.0f},
	
	/*node 14*/
	{.x= 33.0f,  .y= 3.0f, .z= 100.0f},  
	
	/*node 15*/
	{.x= 100.0f, .y= 3.0f, .z= 100.0f},
};

vec4_t check_closes_node(vec4_t* cats_position, vec4_t ignore1, vec4_t ignore2)
{
	float d  = 100.0f; 
	float cd = 0; 
	int   o  = 0;
	int i, j;  
	vec4_t tmp[4];
	
	for(i = 0; i < 16; ++i)
	{
		cd = vv_distance(cats_position, &placements[i]); 
		//making of shit
		
		if (vv_distance(&placements[i], &ignore1) > 0.0f &&
		    vv_distance(&placements[i], &ignore2) > 0.0f)
		{
			if (cd < d)
			{
				o = i; 
				d = cd; 
			}
		}
			
	}
	
	for (i = 0, j = 0; i < 16; ++i)
	{
		 if (vv_distance(cats_position, &placements[i]) <= d+2.0f)
		 {
		 	if (vv_distance(&placements[i], &ignore1) > 0.0f &&
		    	vv_distance(&placements[i], &ignore2) > 0.0f)
		    {
		 		tmp[j] = placements[i];
		 		j++; 
		 	}
		 }
		 
		 if (j >= 3) break;  
	}
	
	//return placements[o];
	return tmp[rand()%j];
}

void cats_init()
{
	load_mesh("Assets/cat.obj", &cat_model); 
	load_png_texture("Assets/cat.png", &cat_tex);	
	
	for(int i = 0; i < MAX_CATS; ++i)
	{
		obj_init(&cats[i]);
		cats[i].model = &cat_model; 
		cats[i].texture = cat_tex; 
		cats[i].box.is_active = 0; 

		rand_cat_select[i] = rand()%16; 
		
		for(int j = 0; j < MAX_CATS; ++j)
		{
			if (rand_cat_select[i] == rand_cat_select[j])
				rand_cat_select[i]++; 
		}
		
		cats[i].pos = placements[rand_cat_select[i]];
		cats[i].pos.y = 1.0f; 
		
		current_node[i] = check_closes_node(&cats[i].pos, vv_one(), vv_one()); 
		last_node[i] = vv_one(); 		 
	} 
	
}

void cats_start()
{

}
 
void cats_update()
{

	//cat.rot.y += 0.6f; 
//printf("time_delta_time() = %f\n", time_delta_time()); 
    vec4_t dir; 
    vec4_t frwd; 
    vec4_t pnorm; 
    vec4_t cnorm; 
	float lookat; 
	
	for(spki = 0; spki < MAX_CATS; ++spki)
	{
		//cats[spki].rot.y += 150.0f * time_delta_time();
		
		
		vv_sub(&dir, &current_node[spki], &cats[spki].pos);
		vv_norm(&dir, &dir);
		
		float r = atan2(dir.x, dir.z)*180/3.14159;
		cats[spki].rot.y = r-180.0f;
		
		vv_rot_y(&frwd, &forward_vec, DEG2RAD(cats[spki].rot.y)); 
		vv_sub(&cnorm, &player_get_objmd2()->pos, &cats[spki].pos);
		//vv_norm(&pnorm, &chest_get_obj()->pos); 
		vv_norm(&cnorm, &cnorm);
		//vv_norm(&cnorm, &cats[spki].pos);
				
		lookat = vv_dot(&cnorm, &frwd); 
		
		//printf("look at = %f\n", lookat);
		if (lookat < -0.90f)
		{
			//printf("distance = %f\n", vv_sqr_distance(&cats[spki].pos, 
			                                    //  &player_get_obj()->pos)); 
			if (vv_sqr_distance(&cats[spki].pos, &player_get_objmd2()->pos) < 2500.0f)            
				player_reset();//printf("caught!!\n");
		}
		cats[spki].pos.x += dir.x * CATS_SPEED * time_delta_time();    
		cats[spki].pos.z += dir.z * CATS_SPEED * time_delta_time();   

		if (vv_sqr_distance(&current_node[spki], &cats[spki].pos) < 4.1f)
		{
			vec4_t tmp = current_node[spki]; 
			
			current_node[spki] = check_closes_node(&cats[spki].pos,   
			                     current_node[spki], last_node[spki]);
			                     
            last_node[spki] = tmp;
		}
		//aabb_update(&cats[spki].box, &cats[spki].pos, &placements[3+(4*spki)]);
		
		aabb_hit(&cats[spki].box, cat_player_box); 
	}
}

void cats_player(aabb_t* aabb)
{
	cat_player_box = aabb; 
}

vec4_t cats_get_placements()
{
	int i = rand()%MAX_CATS; 
	if (last_returned_placement != i)
		last_returned_placement = i; 
	else 
		++i; 
	 
	return placements[i]; 
}
 
obj_t* cats_get_obj(int i)
{
	return &cats[i];
} 

obj_t* cat_get_obj()
{
	//return &cat;
	return NULL;
}

vec4_t* get_placements()
{
	return &placements[0];
}
