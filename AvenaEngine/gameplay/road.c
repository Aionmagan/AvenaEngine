#include "road.h"
#include "player.h" 
#include "../fm/pngloader.h"
#include "../fm/timer.h"
mesh_t road_mesh; 
obj_t road_obj; 

objmt_t road_objmt[2]; 
meshmt_t lvl2_meshmt; 
meshmt_t lvl1_meshmt;

unsigned int now, start; 

void road_init()
{
	load_mesh("Assets/collision_mesh.obj", &road_mesh);
	printf("\nGOT IN\n");
	load_meshmt("Assets/lvl.obj", &lvl1_meshmt);
	//load_meshmt("Assets/VHS_Shop/Textures/lvl2.obj", &lvl2_meshmt);
	printf("\nGOT OUT\n");
	
	load_png_texture("Assets/texture_02.png", &road_obj.texture); 
	road_obj.model = &road_mesh;
	
	obj_init(&road_obj); 
	road_obj.box.is_active = 0; 
	
	objmt_init(&road_objmt[0]);
	//objmt_init(&road_objmt[1]);
	
	for(int i = 0; i < lvl1_meshmt.mesh_parts; ++i)
	{
		char buff[512];
		sprintf(buff, "Assets/%s", lvl1_meshmt.mats[i].texfile);
		//printf("buff %s | i = %d\n",buff, i);
		load_png_texture(buff, &road_objmt[0].texture[i]);
	}
	
/*	for(int i = 0; i < lvl2_meshmt.mesh_parts; ++i)
	{
		char buff[512];
		sprintf(buff, "Assets/VHS_Shop/Textures/%s", lvl2_meshmt.mats[i].texfile);
		//printf("buff %s | i = %d\n",buff, i);
		load_png_texture(buff, &road_objmt[1].texture[i]);
	}
*/	
	//load_png_texture("Assets/texture_02.png", &road_objmt[0].texture[0]); 
	//load_png_texture("Assets/texture_02.png", &road_objmt[1].texture[0]); 
	
	road_objmt[0].model = &lvl1_meshmt; 
//	road_objmt[1].model = &lvl2_meshmt; 
/*
	for(int i = 0; i < road_meshmt.mesh_parts; ++i)
	{
		char buff[512];
		sprintf(buff, "Assets/VHS_Shop/Textures/%s", road_meshmt.mats[i].texfile);
		printf("buff %s | i = %d\n",buff, i);
		load_png_texture(buff, &road_objmt.texture[i]);
	}
*/
	//road_obj.sca.x = 0.6f; 
	//road_obj.sca.y = 0.6f;
	//road_obj.sca.z = 0.6f;  
	//road_obj.pos.z = -15.0f; 
}

void road_update()
{
		start = now;
			now = time_get_tick(); 
		//fpsc = 1.0f / (now-start)*1000.0f; 
		//fpsc = 1000.0f / (now-start); 
		
		//road_obj.sca.x = (1000.0f / (now-start)) * 0.4667f;
}

obj_t* road_get_obj()
{
	return &road_obj;
} 

objmt_t* road_get_mt()
{
	return &road_objmt[0]; 
}

float road_get_u()
{
	return 0.0f; 
}
 
float road_get_v()
{
	return 0.0f; 
} 
