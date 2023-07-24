#include "vec3.h" 

/*vector subtraction*/
void vv_sub(vector_t* out, vector_t* v1, vector_t* v2)
{
	out->point[0] = v1->point[0] - v2->point[0];
	out->point[1] = v1->point[1] - v2->point[1];
	out->point[2] = v1->point[2] - v2->point[2];
}

/*vector addition*/
void vv_add(vector_t* out, vector_t* v1, vector_t* v2)
{
	out->point[0] = v1->point[0] + v2->point[0];
	out->point[1] = v1->point[1] + v2->point[1];
	out->point[2] = v1->point[2] + v2->point[2];
}

/*vector multiplication*/
void vv_mul(vector_t* out, vector_t* v1, vector_t* v2)
{
	out->point[0] = v1->point[0] * v2->point[0];
	out->point[1] = v1->point[1] * v2->point[1];
	out->point[2] = v1->point[2] * v2->point[2];
}

/*vector scalar multiplication*/
void vf_mul(vector_t* out, vector_t* v1, float f)
{
	out->point[0] = v1->point[0] * f;
	out->point[1] = v1->point[1] * f;
	out->point[2] = v1->point[2] * f;
}

/*vector division*/
void vv_div(vector_t* out, vector_t* v1, vector_t* v2)
{
	out->point[0] = v1->point[0] / v2->point[0];
	out->point[1] = v1->point[1] / v2->point[1];
	out->point[2] = v1->point[2] / v2->point[2];
}

