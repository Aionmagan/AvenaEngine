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
	int nx, ny, nz;
}face_t;


typedef struct 
{
	float ambi[4];
	float diff[4];
	float spec[4];
	float emit[4];
	char  texfile[256];
}mat_t; 

typedef struct
{
	vertex_t* verts; 
	uv_t* uvs;       /*not used in psp*/
	face_t* faces;   /*not used in psp*/
	mat_t mat; 
	int face_count; 
}mesh_t;

typedef struct
{
	/*CHANGE TO 'POINTER TO POINTER'*/
	vertex_t* verts;
	vertex_t* norms;
	uv_t* uvs      ;
	face_t** faces;//[9999];
	mat_t* mats; 
	int* face_count; 
	int mesh_parts;  
	char tex_names[9999][256];
}meshmt_t __attribute__((aligned(32))); 

int load_mesh(char* str, mesh_t* mesh);
int load_meshmt(char* str, meshmt_t* mesh);
int load_mat(char* str, char* substr, mat_t* mat); 
void delete_mesh(mesh_t* mesh);

#endif//__MESH_H__
