#include "../aabb.h" 

void aabb_init(aabb_t* a, vec4_t* pos, vec4_t* sca)
{
	vv_sub(&a->min, pos, sca);
	vv_add(&a->max, pos, sca);
	a->is_active = 1; 
	a->hit = 0; 
}

void aabb_update(aabb_t* a, vec4_t* pos, vec4_t* sca)
{
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
