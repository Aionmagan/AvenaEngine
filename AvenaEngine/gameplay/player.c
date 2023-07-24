#include "player.h" 
//#include "car_texture.h"
#include "../fw.h" 
#include "../fm/timer.h"
#include "../fm/obj.h" 
#include <math.h>

anim_state_t anim[]=
{
	{.start = 0, .end = 39, .fps = 5}, /*state 0 | idel*/ 
	{.start = 40, .end = 45, .fps = 5}, /*state 1 | run*/
};

objmd2_t player; 
objmd2_t chs[MAX_CH];
modelData_t* enemy; 

float posz, roty = -30.0f, rotx = 0.0f;//-31.4f; 
float rot; 
float speed = 5.0f; 

void player_init()
{
	objmd2_init(&player, "Assets/ogro.md2", "Assets/ogrobase.png"); 
	enemy = LoadMD2Model("Assets/doom.md2", "Assets/doom.png");
	
	player.sca.x = 0.02f; 
	player.sca.y = 0.02f;
	player.sca.z = 0.02f;  
	player.pos.z = -15.0f; 
	player.pos.y = 0.5f;
	player.rot.x = -90.0f;
	player.box.is_active = 1; 
	player.anim_state = anim; 
	//player.box.sca_offset.x = 0.3f;
	//player.box.sca_offset.y = 0.3f; 
	//player.box.sca_offset.z = 0.3f; 
	
	for(int i = 0; i < MAX_CH; ++i)
	{
		chs[i].model = enemy;//player.model;
		//objmd2_init(&chs[i], "Assets/ogro.md2", "Assets/ogrobase.png");
		chs[i].last_anim_select = 0; 
		chs[i].anim_select = 0; 
		chs[i].lerp = 0.0f;  
		chs[i].anim_state = anim; 
		chs[i].sca.x = 0.02f; 
		chs[i].sca.y = 0.02f; 
		chs[i].sca.z = 0.02f; 
		chs[i].pos.z = player.pos.z - cosf(i*3+i)*1.5f;
		chs[i].pos.y = 0.5f;
		chs[i].pos.x = player.pos.x + sinf(i*3+i)*1.5f;  
		chs[i].rot.x = -90.0f; 
	}
}

void player_start()
{

}

void player_update()
{ 
	//aabb_update(&car.box, &car.pos, &scale); 
	/*
	vec4_t c; 
	vec4_t p; 
	vec4_t np; 
	
	//printf("sqr_distance = %f | distance %f\n", vv_sqr_distance(&player.pos, &chs[0].pos), vv_distance(&player.pos, &chs[0].pos));
	
	vv_negative(&np, &player.pos); 
	vv_norm(&np, &np);
	vv_norm(&p, &player.rot); 
	
	vv_cross(&c, &p, &np);
	*/
	//vv_norm(&c, &c);
	//printf("c = {%f, %f, %f}\n", c.x, c.y, c.z);
	
	if (ctrl_x_axis() != 0 || ctrl_y_axis() != 0)
	{
		player.pos.x += ctrl_x_axis()*speed*time_delta_time(); 
		player.pos.z += ctrl_y_axis()*speed*time_delta_time(); 
		rot = atan2(ctrl_x_axis(), ctrl_y_axis())*180/3.14159;
		player.rot.z = rot-90.0f; 
		//printf("rot.z = %f  |  %f\n", (player.rot.z+90.0f)+180, player.rot.z);
		player.anim_select = ANIMSTATE1; 
		
		for(int i = 0; i < MAX_CH; ++i)
		{
			chs[i].pos.x += ctrl_x_axis()*speed*time_delta_time(); 
			chs[i].pos.z += ctrl_y_axis()*speed*time_delta_time();
			chs[i].rot.z = rot-90.0f; 
			chs[i].anim_select = ANIMSTATE1; 
		}
	}else 
	{
	 	player.anim_select = ANIMSTATE0;
	 	
	 	for(int i = 0; i < MAX_CH; ++i)
		{
			chs[i].anim_select = ANIMSTATE0; 
		}
	}
	
	posz += ctrl_y_axis(); 
	if (ctrl_button(BTN_A))
	{
		roty += ctrl_y_axis();
	}
	
	if (ctrl_button(BTN_B))
	{
		rotx += ctrl_x_axis();
	}
	  
	//printf("roty = %f | posz = %f | atan2() = %f\n", roty, posz, rot);
//printf("A = %d\n", ctrl_button(A));	
//printf("Y = %f\n", ctrl_y_axis());	
	render_cameraf(player.pos.x, player.pos.y+2.0f, player.pos.z+4.0f, rotx, roty, 0.0f); 
	
	
	
	vec4_t one_sca = {.x = 0.3f, .y = 0.3f, .z = 0.3f}; 
	
	aabb_update(&player.box, &player.pos, &one_sca);
	
}
 
objmd2_t* player_get_obj()
{
	return &player; 
}

objmd2_t* ch_get_obj(int i)
{
	return &chs[i]; 
}
