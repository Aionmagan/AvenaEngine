#ifndef __OBJ_H__
#define __OBJ_H__

#include "mesh.h" 
#include "vec4.h" 
#include "aabb.h" 
#include "md2.h"
/*move later to own files*/ 

typedef struct
{
	char* texture; 
	int w, h; 
	int tid; 
}tex_t; 
/*move later to own files*/ 

typedef struct
{
	mesh_t* model;
	tex_t texture; 
	vec4_t pos; 
	vec4_t rot; 
	vec4_t sca;
	aabb_t box; //collider 
	float dens; //color density;  
}obj_t; 

typedef struct
{
	meshmt_t* model;
	tex_t texture[200]; 
	vec4_t pos; 
	vec4_t rot; 
	vec4_t sca;
	int wire; //collider 
	float dens; //color density;  
}objmt_t; 

typedef struct 
{
	modelData_t* model;
	int current_frame; 
	int next_frame;
	float lerp; 
	int anim_select; 
	int last_anim_select;
	anim_state_t* anim_state; 
	vec4_t pos; 
	vec4_t rot; 
	vec4_t sca;
	aabb_t box; //collider 
	float dens; //color density;
}objmd2_t; 

void obj_init(obj_t* obj);
void objmt_init(objmt_t* obj);
void objmd2_init(objmd2_t* obj, char* model, char* texture);

#endif//__OBJ_H__
