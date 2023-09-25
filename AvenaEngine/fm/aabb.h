#ifndef __AABB_H__
#define __AABB_H__

#include "vec4.h" 
#include "mesh.h"
//#include "obj.h" 

//maybe add internal scale and pos
typedef struct 
{
	vec4_t min; 
	vec4_t max; 
	int is_active; 
	int hit; 
	
	/*GOOD IDEA FOR LATER*/ 
	//vec4_t pos_offset; 
	//vec4_t sca_offset; 
	//vec4_t* owner_pos; 
	//vec4_t* owner_sca; 
}aabb_t; 

void aabb_init(aabb_t* a, vec4_t* pos, vec4_t* sca);
void aabb_update(aabb_t* a, vec4_t* pos, vec4_t* sca); 
void aabb_hit(aabb_t* a, aabb_t* b); 
int aabb_overlap(aabb_t* a, aabb_t* b); 

/*should have it's own file but not enough time*/
int mesh_collision(vec4_t* point, mesh_t* mesh); 


#endif//__AABB_H__
