#ifndef __MESH_H__
#define __MESH_H__

#if defined(__PSP__)

typedef struct
{
	float u, v;  
	unsigned int color;  
	float vx, vy, vz; 
	//float nx, ny, nz; 
}vertex_t __attribute__((aligned(16)));

#else

typedef struct
{
	float x, y, z;  
}vertex_t; 

#endif 

typedef struct
{
	float u, v; 
}uv_t; 

typedef struct
{
	int vx, vy, vz; 
	int ux, uy, uz; 
}face_t;

typedef struct
{
	vertex_t* verts; 
	uv_t* uvs;       /*not used in psp*/
	face_t* faces;   /*not used in psp*/
	int face_count; 
}mesh_t;

int load_mesh(char* str, mesh_t* mesh);
void delete_mesh(mesh_t* mesh);

#endif//__MESH_H__
