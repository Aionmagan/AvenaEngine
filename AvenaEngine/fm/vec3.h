#ifndef __VEC3_H__
#define __VEC3_H__

typedef struct 
{
	float point[3]; 
}vector3_t; 

/*vector subtraction*/
void vv3_sub(vector3_t* out, vector3_t* v1, vector3_t* v2);

/*vector addition*/
void vv3_add(vector3_t* out, vector3_t* v1, vector3_t* v2);

/*vector multiplication*/
void vv3_mul(vector3_t* out, vector3_t* v1, vector3_t* v2);

/*vector scalar multiplication*/
void vf3_mul(vector3_t* out, vector3_t* v1, float f);

/*vector division*/
void vv3_div(vector3_t* out, vector3_t* v1, vector3_t* v2);

/*vector interpolation*/
void vv3_lerp(vector3_t* out, vector3_t* v1, vector3_t* v2, float l); 

#endif//__VEC3_H__
