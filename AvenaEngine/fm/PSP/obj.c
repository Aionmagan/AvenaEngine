#include "../obj.h" 

void obj_init(obj_t* obj)
{
	obj->pos.x = 0; 
	obj->pos.y = 0; 
	obj->pos.z = 0;
	obj->sca.x = 1.0f; 
	obj->sca.y = 1.0f; 
	obj->sca.z = 1.0f; 
	obj->rot.x = 0; 
	obj->rot.y = 0; 
	obj->rot.z = 0; 
	obj->dens = 1.0f; 
	
	aabb_init(&obj->box, &obj->pos, &obj->sca); 
}
