#ifndef __VEC4_H__
#define __VEC4_H__

#include <math.h>

typedef struct
{
	float x, y, z, w;
}vec4_t; 

static float vv_length(vec4_t* v)
{
    return sqrt((v->x*v->x) + (v->y*v->y) + (v->z*v->z));
}

static float vv_sqr_length(vec4_t* v)
{
	return (v->x*v->x) + (v->y*v->y) + (v->z*v->z);
}

static float vv_sqr_distance(vec4_t* v1, vec4_t* v2)
{
	//float x = (v1->x - v2->x); 
	//float y = (v1->y - v2->y); 
	//float z = (v1->z - v2->z); 
	
	//return x*x + y*y + z*z; 
	
	return ((v1->x - v2->x)*(v1->x - v2->x)) + 
	       ((v1->y - v2->y)*(v1->y - v2->y)) + 
	       ((v1->z - v2->z)*(v1->z - v2->z));
	//return (v1->x*v1->x) - (v2->x*v2->x) - (v1->y*v1->y);
}

static float vv_distance(vec4_t* v1, vec4_t* v2)
{
	return sqrt(vv_sqr_distance(v1, v2)); 
}

static float vv_dot(vec4_t* v1, vec4_t* v2)
{
	return (v1->x*v2->x) + (v1->y*v2->y) + (v1->z*v2->z); 
}

static void vv_cross(vec4_t* out, vec4_t* v1, vec4_t* v2)
{
	out->x = v1->y * v2->z - v1->z * v2->y;
	out->y = v1->z * v2->x - v1->x * v2->z; 
	out->z = v1->x * v2->y - v1->y * v2->x; 
}

static void vv_negative(vec4_t* out, vec4_t* v)
{
	out->x = -v->x;
	out->y = -v->y; 
	out->z = -v->z; 
}

static void vv_sub(vec4_t* out, vec4_t* v1, vec4_t* v2)
{
	//vec4_t tmp; 
	out->x = v1->x - v2->x;
	out->y = v1->y - v2->y;
	out->z = v1->z - v2->z; 
	//return tmp; 
}

static void vv_add(vec4_t* out, vec4_t* v1, vec4_t* v2)
{
	//vec4_t tmp; 
	out->x = v1->x + v2->x;
	out->y = v1->y + v2->y;
	out->z = v1->z + v2->z; 
	//return tmp; 
}

static void vv_lerp(vec4_t* out, vec4_t* v1, vec4_t* v2, float l)
{
	//vec4_t tmp; 
	out->x = v1->x + l * (v2->x - v1->x);
	out->y = v1->y + l * (v2->y - v1->y);
	out->z = v1->z + l * (v2->z - v1->z);
	//out->w = 1.0f; 
	//return tmp; 
}

/*put in f math in the future*/
static float ff_lerp(float f1, float f2, float l)
{
	return (f1 + l * (f2 - f1)); 
} 

static void vv_norm(vec4_t* out, vec4_t* v)
{
	float l = vv_length(v); 
	
	out->x = v->x/l; 
	out->y = v->y/l; 
	out->z = v->z/l; 
}

/*vector 1*/ 
static vec4_t vv_one()
{
	vec4_t tmp; 
	tmp.x = 1.0f;
	tmp.y = 1.0f; 
	tmp.z = 1.0f;  
	return tmp;
}

#endif//__VEC4_H__
