#include "../vec3.h" 

/*vector subtraction*/
void vv3_sub(vector3_t* out, vector3_t* v1, vector3_t* v2)
{
	out->point[0] = v1->point[0] - v2->point[0];
	out->point[1] = v1->point[1] - v2->point[1];
	out->point[2] = v1->point[2] - v2->point[2];
}

/*vector addition*/
void vv3_add(vector3_t* out, vector3_t* v1, vector3_t* v2)
{
	out->point[0] = v1->point[0] + v2->point[0];
	out->point[1] = v1->point[1] + v2->point[1];
	out->point[2] = v1->point[2] + v2->point[2];
}

/*vector multiplication*/
void vv3_mul(vector3_t* out, vector3_t* v1, vector3_t* v2)
{
	out->point[0] = v1->point[0] * v2->point[0];
	out->point[1] = v1->point[1] * v2->point[1];
	out->point[2] = v1->point[2] * v2->point[2];
}

/*vector scalar multiplication*/
void vf3_mul(vector3_t* out, vector3_t* v1, float f)
{
	out->point[0] = v1->point[0] * f;
	out->point[1] = v1->point[1] * f;
	out->point[2] = v1->point[2] * f;
}

/*vector division*/
void vv3_div(vector3_t* out, vector3_t* v1, vector3_t* v2)
{
	out->point[0] = v1->point[0] / v2->point[0];
	out->point[1] = v1->point[1] / v2->point[1];
	out->point[2] = v1->point[2] / v2->point[2];
}

/*vector interpolation*/
void vv3_lerp(vector3_t* out, vector3_t* v1, vector3_t* v2, float l)
{
	out->point[0] = v1->point[0] + l * (v2->point[0] - v1->point[0]);
	out->point[1] = v1->point[1] + l * (v2->point[1] - v1->point[1]);
	out->point[2] = v1->point[2] + l * (v2->point[2] - v1->point[2]);
}
