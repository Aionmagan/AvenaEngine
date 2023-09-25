#include "player.h" 
#include "ui.h"
//#include "car_texture.h"
#include "../fw.h" 
#include "../fm/timer.h"
#include "../fm/obj.h" 
#include "ui.h"
#include "../modes.h"
#include <math.h>
 
#define CAMERA_VIEW_OFFSET 40.0f

mesh_t collision_mesh; 

mesh_t mesh_player; 
obj_t  player;

objmd2_t md2_player; 

int dead = 0; 
float cspeed = 80.0f; 

vec4_t starting_pos; 
vec4_t pos; 
vec4_t rot; 
vec4_t lastPos; 
vec4_t box_sca = {3.0f, 3.0f, 3.0f};

vec4_t fpsrot; 
vec4_t fpspos; 

anim_state_t anim[]=
{
	{.start = 0, .end = 9, .fps = 5}, /*state 0 | idel*/ 
	{.start = 10, .end = 30, .fps = 50}, /*state 1 | run*/
	//{.start = 17, .end = 18, .fps = 5},/*state 2 | jump*/
	// {.start = 10, .end = 16, .fps = 10}, /*state 1 | run*/
};

void player_init()
{
	//load_mesh("Assets/rat.obj", &mesh_player);
	//load_png_texture("Assets/rat.png", &player.texture); 
	
	load_mesh("Assets/meshCollider.obj", &collision_mesh);
	
	objmd2_init(&md2_player, "Assets/rat.md2", "Assets/rat.png"); 
	md2_player.anim_state = anim; 
	
	md2_player.rot.x = -90.0f;
	md2_player.rot.z = -90.0f; 
	
	//player.model = &mesh_player; 
	
	//camera
	pos.y = 82.0f; 
	pos.z = 60.0f; 
	rot.y = -60.0f; 
	
	
    starting_pos.x = -0.5f; 
	starting_pos.y = 3.0f; 
	starting_pos.z = 150.0f; 
	//obj_init(&player);
	//player.box.is_active = 1;
	//md2_player.pos.x = 23.0f;
	//md2_player.pos.y = 3.0f; 
	//md2_player.pos.z = 13.0f; 
	
	md2_player.pos = starting_pos; 
	
	lastPos = md2_player.pos; 
}

void player_start()
{
	player.pos.z = -15.0f; 
	player.pos.y = 0.5f;
	player.pos.x = -28.0f;
}

void player_update()
{ 
	float s = cspeed * time_delta_time();// * time_delta_ti me(); 	
	int ct = 0; 
	vec4_t dir={0}; 
	//printf("Player {%f, %f, %f}\n", md2_player.pos.x, md2_player.pos.y, md2_player.pos.z); 
	
	if (!ctrl_button(BTN_A))
	{			
		//md2_player.pos.z += ctrl_y_laxis() * s; 
		//md2_player.pos.x += ctrl_x_laxis() * s; 
		
		dir.z += ctrl_y_laxis(); 
		dir.x += ctrl_x_laxis(); 
		
		vv_norm(&dir, &dir); 
		
		md2_player.pos.z += dir.z * s; 
		md2_player.pos.x += dir.x * s; 
		
	    if (ctrl_x_laxis() != 0 || ctrl_y_laxis() != 0)
		{
			float r = RAD2DEG(atan2(ctrl_x_laxis(), ctrl_y_laxis()));
			md2_player.rot.z = r+90.0f; 
			
			md2_player.anim_select = ANIMSTATE1;
		}else{
#if defined(__PSV__)
			md2_player.anim_select = ANIMSTATE1; 
#else
			md2_player.anim_select = ANIMSTATE0;
#endif						
		}
		
		ct = mesh_collision(&md2_player.pos, &collision_mesh);

		if (ct)
		{
			lastPos = md2_player.pos; 
		}else 
		{
			md2_player.pos = lastPos; 
		}	
		
		//pos.z = player.pos.z + 47.0f; 
		//pos.x = player.pos.x; 
		
		
	    if (ctrl_x_raxis() != 0 || ctrl_y_raxis() != 0)
	    {
			pos.z = ff_lerp(pos.z, (md2_player.pos.z+47.0f) + 
			                ctrl_y_raxis() * CAMERA_VIEW_OFFSET, 0.2f);
		
		    pos.x = ff_lerp(pos.x, (md2_player.pos.x)+
		                    ctrl_x_raxis() * CAMERA_VIEW_OFFSET, 0.2f);  	    
	    }else{	   
			pos.z = ff_lerp(pos.z, md2_player.pos.z + 47.0f, 0.2f); 
			pos.x = ff_lerp(pos.x, md2_player.pos.x, 0.2f); 		
		}
		
	}else
	{
/*		if (ctrl_button(BTN_B))
		{
			pos.y -= ctrl_y_laxis() * s; 
		}else
		{
			//pos.z = (player.pos.z+47.0f) + ctrl_y_axis() * CAMERA_VIEW_OFFSET;
			pos.z = ff_lerp(pos.z, (player.pos.z+47.0f) + ctrl_y_laxis() * CAMERA_VIEW_OFFSET, 0.2f);
			
		}
*/
		
		pos.z = ff_lerp(pos.z, (md2_player.pos.z+47.0f) + ctrl_y_laxis() * CAMERA_VIEW_OFFSET, 0.2f);
		
		//pos.x = (player.pos.x)+ctrl_x_axis() * CAMERA_VIEW_OFFSET;  
		pos.x = ff_lerp(pos.x, (md2_player.pos.x)+ctrl_x_laxis() * CAMERA_VIEW_OFFSET, 0.2f);  
		
		/*if (ctrl_button(BTN_A))
			rot.y -= s; 
		if (ctrl_button(BTN_X))
			rot.y += s;  */
	}	
	
	//md2_player.pos = player.pos; 
	//md2_player.rot.x = -90;//player.rot.x; 
	//md2_player.rot.y = 0;//player.rot.y; 
	//md2_player.rot.z = player.rot.y-90;//-player.rot.y+90; 
	
	
	aabb_update(&md2_player.box, &md2_player.pos, &box_sca);
	
	render_cameraf(pos.x, pos.y, pos.z, rot.x, rot.y, rot.z); 
#if 0	
	if (ctrl_button(BTN_X))
	{
		if (ctrl_x_laxis() != 0 || ctrl_y_laxis() != 0)
		{
			fpspos.x += ctrl_x_laxis() * s;
			fpspos.z += ctrl_y_laxis() * s; 
		}
		
		if (ctrl_button(BTN_Y))
			fpspos.y += ctrl_y_laxis() * s; 
			
		if (ctrl_x_raxis() != 0 || ctrl_y_raxis() != 0)
		{
			fpsrot.x += ctrl_x_raxis() * s; 
			fpsrot.y += ctrl_y_raxis() * s; 
		}
	}
	
	render_cameraf(fpspos.x, fpspos.y, fpspos.z, fpsrot.x, fpsrot.y, fpsrot.z); 
#endif
}

int player_is_alive()
{
	if (dead)
		return 1; 
	return 0;
}

void player_reset()
{
	md2_player.pos = starting_pos; 
	lastPos = starting_pos; 
	printf("caught!!\n");
	ui_cheese_reset();
}
 
obj_t* player_get_obj()
{
	return &player; 
}

objmd2_t* player_get_objmd2()
{
	return &md2_player; 
}
