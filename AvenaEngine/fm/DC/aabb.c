#include "../aabb.h" 

void aabb_init(aabb_t* a, vec4_t* pos, vec4_t* sca)
{
	/*o->box.min.x = o->pos.x - o->sca.x;
	o->box.min.y = o->pos.y - o->sca.y;
	o->box.min.z = o->pos.z - o->sca.z;
	
	o->box.max.x = o->pos.x - o->sca.x;
	o->box.max.y = o->pos.y - o->sca.y;
	o->box.max.z = o->pos.z - o->sca.z; 
	*/
	//o->box = vv_sub(&o->pos, &o->sca); 
	
	//a->min = vv_sub(pos, sca); 
	//a->max = vv_add(pos, sca); 
	
	vv_sub(&a->min, pos, sca);
	vv_add(&a->max, pos, sca);
	a->is_active = 1; 
	a->hit = 0; 
}

void aabb_update(aabb_t* a, vec4_t* pos, vec4_t* sca)
{
	//o->box.min.x = o->pos.x-box.min.x; 
	//o->box.	
	
	//a->min = vv_sub(pos, &a->min);
	//a->max = vv_add(pos, &a->max); 
	//a->min = vv_sub(pos, sca); 
	//a->max = vv_add(pos, sca); 
	vv_sub(&a->min, pos, sca);
	vv_add(&a->max, pos, sca); 
	a->hit = 0; 
}

void aabb_hit(aabb_t* a, aabb_t* b)
{
	if (aabb_overlap(a, b))
	{
		a->hit = 1; 
		b->hit = 1; 
	}
}

int aabb_overlap(aabb_t* a, aabb_t* b)
{
	return(a->max.x > b->min.x &&
    	   a->min.x < b->max.x &&
    	   a->max.y > b->min.y &&
    	   a->min.y < b->max.y &&
    	   a->max.z > b->min.z &&
    	   a->min.z < b->max.z);
} 
