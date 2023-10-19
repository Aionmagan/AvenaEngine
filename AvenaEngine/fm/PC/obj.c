#include "../obj.h" 
#include <stdio.h>

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

void objmt_init(objmt_t* obj)
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
	
	//aabb_init(&obj->box, &obj->pos, &obj->sca); 
}

void objmd2_init(objmd2_t* obj, char* model, char* texture)
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
	
	/*good idea for later*/
	//obj->box.owner_pos = &obj->pos; 
	//obj->box.owner_sca = &obj->sca; 
	
	aabb_init(&obj->box, &obj->pos, &obj->sca); 
		
	if (model == NULL || texture == NULL)
		return; 
		
	obj->model = LoadMD2Model(model, texture);
	obj->current_frame = obj->model->currentFrame; 
	obj->next_frame = obj->model->nextFrame; 
	obj->last_anim_select = 0; 
	obj->anim_select = 0; 
	obj->lerp = 0.0f; 
}
