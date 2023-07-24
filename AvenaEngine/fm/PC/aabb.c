#include "../aabb.h" 

//vec4_t offset_pos; 
//vec4_t offset_sca; 

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
	//vv_sub(&offset_pos, a->owner_pos, &a->pos_offset);
	//vv_sub(&offset_sca, a->owner_sca, &a->sca_offset);
	//printf("owner_pos = {%f, %f, %f}\n", a->owner_pos->x, a->owner_pos->y, a->owner_pos->z);
	//vv_sub(&a->min, &offset_pos, &offset_sca);
	//vv_add(&a->max, &offset_pos, &offset_sca);
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
