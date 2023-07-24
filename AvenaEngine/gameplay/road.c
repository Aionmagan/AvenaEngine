#include "road.h"
#include "../fm/pngloader.h"
#include "../fm/timer.h"
mesh_t road_mesh; 
obj_t road_obj; 
unsigned int now, start; 
void road_init()
{
	load_mesh("Assets/lvl.obj", &road_mesh);
	load_png_texture("Assets/lvl1.png", &road_obj.texture); 
	road_obj.model = &road_mesh;
	
	obj_init(&road_obj); 
	road_obj.box.is_active = 0; 
	road_obj.sca.x = 28.0f; 
	road_obj.sca.y = 28.0f;
	road_obj.sca.z = 28.0f;  
	road_obj.pos.z = -15.0f; 
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

float road_get_u()
{
	return 0.0f; 
}
 
float road_get_v()
{
	return 0.0f; 
} 
