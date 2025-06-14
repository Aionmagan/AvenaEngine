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
	if (a->is_active == 0 || b->is_active == 0)
		return 0; 
		
	return(a->max.x > b->min.x &&
    	   a->min.x < b->max.x &&
    	   a->max.y > b->min.y &&
    	   a->min.y < b->max.y &&
    	   a->max.z > b->min.z &&
    	   a->min.z < b->max.z);
} 

/*should have it's own file but not enough time*/
int ptInTriangle(vec4_t p, vertex_t p0, vertex_t p1, vertex_t p2) 
{
	//printf("P{%f, %f} | P0{%f, %f} | P1{%f, %f} | P2{%f, %f}\n", p.x, p.z, p0.x, p0.z, p1.x, p1.z, p2.x, p2.z); 
    float A = 0.5f * (-p1.z * p2.x + p0.z * (-p1.x + p2.x) + p0.x * (p1.z - p2.z) + p1.x * p2.z);
    float sign = A < 0 ? -1.0f : 1.0f;
    float s = (p0.z * p2.x - p0.x * p2.z + (p2.z - p0.z) * p.x + (p0.x - p2.x) * p.z) * sign;
    float t = (p0.x * p1.z - p0.z * p1.x + (p0.z - p1.z) * p.x + (p1.x - p0.x) * p.z) * sign;
    
    //printf("A = %f, S = %f, T = %f\n", A, s, t);
    return (s > 0 && t > 0 && (s + t) < 2 * A * sign);
}

int mesh_collision(float* yout, vec4_t* point, mesh_t* mesh)
{
    int A, A1, A2, A3; 
	float r; 
	int i; 
	for(i = 0; i < mesh->face_count; ++i)
	{

		//printf("\n player {%f , %f}  |  vertex {%f , %f}\n", player->x, player->z,
//		mesh_test.verts[mesh_test.faces[i].vx].x,
	//	mesh_test.verts[mesh_test.faces[i].vx].z);
		A = ptInTriangle(*point, 
		    mesh->verts[mesh->faces[i].vx],
		    mesh->verts[mesh->faces[i].vy],
		    mesh->verts[mesh->faces[i].vz]);
		    
		//printf("A = %d\n", A);
		if (A)
		{
			*yout = mesh->verts[mesh->faces[i].vx].y;
			return 1; 	       		
		}       		
			
		//printf("called \n");
	}
	
	return 0;
}
