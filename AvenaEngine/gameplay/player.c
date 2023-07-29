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
vec4_t dir, cdir; 

float posz, roty = -20.0f, rotx = 0.0f;//-31.4f; 
float rot, crotx; 
float cam_rot; 
float cam_target_rot;

float center_cam = 0; 
float speed = 5.0f; 

void player_init()
{
	objmd2_init(&player, "Assets/ogro.md2", "Assets/ogrobase.png"); 
	
	cdir.z = 1.0f;
	cdir.x = 0.0f;
	//vv_rot_y(&dir, &cdir, DEG2RAD(0.0f));
	cam_rot = player.rot.z;
	
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
		//player.pos.x += ctrl_x_axis()*speed*time_delta_time(); 
		//player.pos.z += ctrl_y_axis()*speed*time_delta_time(); 
		cdir.x = ctrl_x_axis();
		cdir.z = ctrl_y_axis(); 
		
		rot = atan2(ctrl_x_axis(), ctrl_y_axis())*180/3.14159;
		player.rot.z = rot-90.0f+cam_rot; 
		//if (fabsf(player.rot.z) > 360.0f) player.rot.z = 0; 
		//crotx += ctrl_x_axis(); 
		//dir.x = ctrl_x_axis(); 
		//dir.z = ctrl_y_axis(); 
		//printf("dir = {%f, %f, %f} | rot = %f\n", dir.x, dir.y, dir.z, rot+180.0f);
		vv_rot_y(&dir, &cdir, DEG2RAD(cam_rot)); 
		
		vf_mul(&dir, &dir, speed*time_delta_time());
		
		vv_add(&player.pos, &player.pos, &dir);
		
		//printf("rot.z = %f  |  %f\n", (player.rot.z+90.0f)+180, player.rot.z);
		player.anim_select = ANIMSTATE1; 
		
	}else 
	{
	 	player.anim_select = ANIMSTATE0;
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
	
	if (ctrl_button_down(BTN_X))
	{
		center_cam = 1;  
		cam_target_rot = player.rot.z-90.0f; 
		if (cam_target_rot < -360.0f) 
			cam_target_rot = cam_target_rot + 360.0f; 
		printf("rotx = %f | cam_target_rot = %f\n", rotx, cam_target_rot);
	}
	
	if(center_cam)
	{
		//crotx = rot-180.0f; //0-360
		//if (crotx >= 360.0f) crotx = 0.03f; 
		//if (crotx <= 0.01f) crotx = 359.0f; 
		//if (rot+180.0f > 359.0f) rotx = 1.0f; 
		//if (rot+180.0f < 1.0f) rotx = 359.0f; 
		//rotx = ff_lerp(rotx, cam_target_rot, 0.5f);
		rotx = ff_move_towards(rotx, cam_target_rot, 0.5f);
		//rotx = cam_target_rot;
		//rotx = ff_move_towards(cam_target_rot, rotx, 0.5f);
		//if (rot+180.0f > 359.0f) rotx = 1.0f; 
		//if (rot+180.0f < 1.0f) rotx = 359.0f; 

		float r = fabsf(fabsf(rotx) - fabsf(cam_target_rot));
		//printf("rotx - rot-180.0f = %f, %f\n", r, rotx);
		if (r <= 0.1f)//???? wtf
		{
			
			//vv_rot_y(&dir, &cdir, DEG2RAD(player.rot.z));
			cam_rot = cam_target_rot;
			center_cam = 0; 
		}
	}
	  
	//printf("roty = %f | posz = %f | atan2() = %f\n", roty, posz, rot);
//printf("A = %d\n", ctrl_button(A));	
//printf("Y = %f\n", ctrl_y_axis());	
	render_cameraf(player.pos.x, player.pos.y+2.0f, player.pos.z+4.0f, rotx, roty, 0.0f); 
	//render_camera_lookat(player.pos.x, player.pos.y+0.7f, player.pos.z, rotx, roty, 0.0f, 3.0f);
	
	
	
	vec4_t one_sca = {.x = 0.3f, .y = 0.3f, .z = 0.3f}; 
	
	aabb_update(&player.box, &player.pos, &one_sca);
	
}
 
objmd2_t* player_get_obj()
{
	return &player; 
}
