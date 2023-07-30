#include "player.h" 
//#include "car_texture.h"
#include "../fw.h" 
#include "../fm/timer.h"
#include "../fm/obj.h" 
#include <math.h>

anim_state_t anim[]=
{
	{.start = 0, .end = 2, .fps = 5}, /*state 0 | idel*/ 
	{.start = 3, .end = 9, .fps = 10}, /*state 1 | run*/
	{.start = 17, .end = 18, .fps = 5},/*state 2 | jump*/
	{.start = 10, .end = 16, .fps = 10}, /*state 1 | run*/
};

objmd2_t player;  

vec4_t dir, cdir; 
vec4_t cam_offset; 
vec4_t cam_ori;
vec4_t cam_pos;  
vec4_t vel ={0}; 
vec4_t gra ={.x=0, .y=-2.87f, .z=0};

float posz, roty = -13.0f, rotx = 0.0f;//-31.4f; 
float rot, crotx; 
float cam_rot; 
float cam_target_rot;

float center_cam = 0; 
float speed = 0.3f; 

int on_ground; 
int can_jump; 

void player_init()
{
	objmd2_init(&player, "Assets/manny.md2", "Assets/ogrobase.png"); 
	
	cdir.z = 1.0f;
	cdir.x = 0.0f;
	//vv_rot_y(&dir, &cdir, DEG2RAD(0.0f));
	cam_rot = player.rot.z;
	
	player.sca.x = 0.7f; 
	player.sca.y = 0.7f;
	player.sca.z = 0.7f;  
	player.pos.z = -15.0f; 
	player.pos.y = 0.5f;
	player.pos.x = -28.0f;
	player.rot.x = -90.0f;
	player.box.is_active = 1; 
	player.anim_state = anim; 
	
	on_ground = 0; 
	can_jump = 0; 
	//player.box.sca_offset.x = 0.3f;
	//player.box.sca_offset.y = 0.3f; 
	//player.box.sca_offset.z = 0.3f; 
}

void player_start()
{
 	player.pos.z = -15.0f; 
	player.pos.y = 0.5f;
	player.pos.x = -15.0f;
}

void player_update()
{ 
	if (ctrl_button_down(BTN_A))
	{
		if (can_jump)
		{
			vel.y = 0.8f; 
			can_jump = 0;
		}
	}

	if (ctrl_x_axis() != 0 || ctrl_y_axis() != 0)
	{
		rot = atan2(ctrl_x_axis(), ctrl_y_axis())*180/3.14159;
		player.rot.z = rot-90.0f+cam_rot; 
	}
	
	if (on_ground)
	{
		if (ctrl_x_axis() != 0 || ctrl_y_axis() != 0)
		{ 	
			//vf_mul(&vel, &vel, time_delta_time());
			//vv_add(&player.pos, &player.pos, &vel);
		
			vel.x = ctrl_x_axis()*speed; 
			vel.z = ctrl_y_axis()*speed;
			
			

			
			//player.pos.x += ctrl_x_axis()*speed*time_delta_time(); 
			//player.pos.z += ctrl_y_axis()*speed*time_delta_time(); 
			cdir.x = ctrl_x_axis();
			cdir.z = ctrl_y_axis(); 

			vv_rot_y(&dir, &cdir, DEG2RAD(cam_rot)); 
			
			vf_mul(&dir, &dir, speed*time_delta_time());
			
			vv_add(&player.pos, &player.pos, &dir);
			
			//printf("rot.z = %f  |  %f\n", (player.rot.z+90.0f)+180, player.rot.z);
			player.anim_select = ANIMSTATE1; 
			
		}else 
		{
			
		 	player.anim_select = ANIMSTATE0;
		}
	}else 
	{
		player.anim_select = ANIMSTATE2; 
		if (ctrl_x_axis() != 0 || ctrl_y_axis() != 0)
		{
			vel.x = ctrl_x_axis()*speed*0.7f; 
			vel.z = ctrl_y_axis()*speed*0.7f;
		}
	}
	
	//vv_add(&vel, &vel, &gra);
	vel.x = vel.x + gra.x * time_delta_time();
	vel.y = vel.y + gra.y * time_delta_time();
	vel.z = vel.z + gra.z * time_delta_time();
	vv_add(&player.pos, &player.pos, &vel);
	//vf_mul(&vel, &vel, time_delta_time()); 
		//printf("Vel = {%f, %f, %f}\n", vel.x, vel.y, vel.z);
	//player.pos.x = player.pos.x + vel.x; 
	//player.pos.y = player.pos.y + vel.y; 
	//player.pos.z = player.pos.z + vel.z; 
	//vv_add(&player.pos, &player.pos, &vel);
	
	if (player.pos.y <= 0.5f)
	{
		can_jump = 1; 
		on_ground = 1; 
		player.pos.y = 0.5f; 
		vv_zero(&vel);
	}else 
	{
		on_ground = 0; 
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
	
	if (ctrl_button_down(BTN_Y))
	{
		player.pos.z = -15.0f; 
		player.pos.y = 0.5f;
		vv_zero(&vel);
	}
	
/*	if (ctrl_button_down(BTN_X))
	{
		center_cam = 1;  
		cam_target_rot = player.rot.z-90.0f; 
		if (cam_target_rot < -360.0f) 
			cam_target_rot = cam_target_rot + 360.0f; 
		printf("rotx = %f | cam_target_rot = %f\n", rotx, cam_target_rot);
	}
*/
	if(center_cam)
	{

		rotx = ff_move_towards(rotx, cam_target_rot, 0.5f);

		float r = fabsf(fabsf(rotx) - fabsf(cam_target_rot));
		if (r <= 0.1f)//???? wtf
		{
			
			//vv_rot_y(&dir, &cdir, DEG2RAD(player.rot.z));
			cam_rot = cam_target_rot;
			center_cam = 0; 
		}
	}
	 
	//cam_pos.x = player.pos.x; 
	//cam_pos.y = -(player.pos.z)*0.35f;
	//cam_pos.z = player.pos.z+4.0f;  
	
	//cam_ori.y = roty+(player.pos.z*2.5f); 
	
	//printf("player.pos.z = %f\n", cam_ori.y);
	//printf("player pos = {%f, %f, %f}\n", player.pos.x, player.pos.y, player.pos.z);
	
	if (player.pos.x < -28.5f)
		player.pos.x = -28.5f; 
	
	if (player.pos.x > 28.3f)
		player.pos.x = 28.3f; 
	
		
	if (player.pos.z < -20.5f)
		player.pos.z = -20.5f; 
		
	if (player.pos.z > -13.0f)
		player.pos.z = -13.0f; 
	
	//if (cam_pos.y <= 5.17f)
		//cam_pos.y = 5.17f; 
	cam_offset.x = player.pos.x; 
	cam_offset.y = player.pos.y + 2.0f; 
	cam_offset.z = player.pos.z + 4.0f;
	
	if (cam_offset.x < -27.0f)
		cam_offset.x = -27.0f; 
		
	if (cam_offset.x > 27.0f)
		cam_offset.x = 27.0f; 
	
	if (cam_offset.z > -10.25f)
		cam_offset.z = -10.25f;
	//vv_lerp(&cam_pos, &cam_pos, &cam_offset, 0.3f); 
	
	//render_cameraf(cam_pos.x, cam_pos.y, cam_pos.z, rotx, cam_ori.y, 0.0f); 
	//render_cameraf(cam_pos.x, cam_pos.y, cam_pos.z, rotx, -30.0f, 0.0f); 
	//render_cameraf(player.pos.x, player.pos.y+2.0f, player.pos.z+4.0f, rotx, roty, 0.0f);
	render_cameraf(cam_offset.x, cam_offset.y, cam_offset.z, rotx, roty, 0.0f); 
	//render_camera_lookat(player.pos.x, player.pos.y+0.7f, player.pos.z, rotx, roty, 0.0f, 3.0f);
	
	
	vec4_t one_sca = {.x = 0.2f, .y = 0.3f, .z = 0.2f}; 
	
	aabb_update(&player.box, &player.pos, &one_sca);
	
}
 
objmd2_t* player_get_obj()
{
	return &player; 
}
