#include "player.h" 
#include "ui.h"
//#include "car_texture.h"
#include "../fw.h" 
#include "../fm/timer.h"
#include "../fm/obj.h" 
#include "ui.h"
#include "../modes.h"
#include <math.h>

#define LOOKAT_DOOR_AMOUNT 1500
#define CAMERA_VIEW_OFFSET 40.0
#define ANALOG_SPEED 17.0 * 4 

vec4_t fwrd={0.0f, 0.0f, 1.0f};
vec4_t rght={1.0f, 0.0f, 0.0f};
vec4_t forward={0.0f, 0.0f, 1.0f};
vec4_t right={1.0f, 0.0f, 0.0f};
vec4_t position = {0};
vec4_t rotation = {0};

mesh_t collision_mesh[2]; 

int dead = 0; 
int get_lvl = 0; 

int lookat_door = 0; 
long lookat_timer = 0; 

vec4_t starting_pos; 
vec4_t lastPos; 
vec4_t box_pos; 
vec4_t box_sca = {7.0f, 10.0f, 7.0f};

aabb_t box; 

void player_init()
{
	//for collision checking the lvl	
	load_mesh("Assets/lvl1Collision.obj", &collision_mesh[0]);
	load_mesh("Assets/lvl2Collision.obj", &collision_mesh[1]);

	//camera starting point	
    starting_pos.x = -80.0f; 
	starting_pos.y =  0.0f; 
	starting_pos.z = 490.0f; 
	
	position = starting_pos; 
	lastPos = position; 
	
	box_pos.x = position.x; 
	box_pos.y = position.y + 5.0f; 
	box_pos.z = position.z; 
	
	aabb_init(&box, &box_pos, &box_sca);
}

void player_start()
{
	//player.pos.z = -15.0f; 
	//player.pos.y = 0.5f;
	//player.pos.x = -28.0f;
	
	position = starting_pos; 
	rotation.x = 0; 
	rotation.y = 0; 
}

void player_update()
{ 
	int ct = 0; 	
	
	box_pos.x = position.x; 
	box_pos.y = position.y + 15.0f; 
	box_pos.z = position.z; 
	
	aabb_update(&box, &box_pos, &box_sca);
	
#if 1		
	vv_rot_y(&forward, &fwrd, DEG2RAD(rotation.x));
	vv_rot_y(&right, &rght, DEG2RAD(rotation.x)); 
	
#if defined(__DC__)
	/*if (ctrl_button(BTN_A))
		rotation.y -=  1.0f * ANALOG_SPEED * time_delta_time();
	else if (ctrl_button(BTN_Y))
		rotation.y -= -1.0f * ANALOG_SPEED * time_delta_time();
		
	if (ctrl_button(BTN_X))
		rotation.x -= -1.0f * ANALOG_SPEED * time_delta_time();
	else if (ctrl_button(BTN_B))
		rotation.x -=  1.0f * ANALOG_SPEED * time_delta_time();	
	*/
	forward.x *= ctrl_y_laxis() * ANALOG_SPEED * time_delta_time();
	forward.y *= ctrl_y_laxis() * ANALOG_SPEED * time_delta_time();
	forward.z *= ctrl_y_laxis() * ANALOG_SPEED * time_delta_time();
	
	//right.x *= ctrl_x_laxis() * ANALOG_SPEED * time_delta_time();
	//right.y *= ctrl_x_laxis() * ANALOG_SPEED * time_delta_time();
	//right.z *= ctrl_x_laxis() * ANALOG_SPEED * time_delta_time();
	
	rotation.x -= ctrl_x_laxis() * ANALOG_SPEED * time_delta_time();
	
	if (ctrl_button(BTN_X))
	{
		right.x *= -1.0f * ANALOG_SPEED * time_delta_time();
	    right.y *= -1.0f* ANALOG_SPEED * time_delta_time();
	    right.z *= -1.0f * ANALOG_SPEED * time_delta_time();
	}else if (ctrl_button(BTN_B))
	{
		right.x *= 1.0f * ANALOG_SPEED * time_delta_time();
	    right.y *= 1.0f * ANALOG_SPEED * time_delta_time();
	    right.z *= 1.0f * ANALOG_SPEED * time_delta_time();
	}else 
	{
		right.x *= 0.0f;
	    right.y *= 0.0f;
	    right.z *= 0.0f;
	}
	
#else
	forward.x *= ctrl_y_laxis() * ANALOG_SPEED * time_delta_time();
	forward.y *= ctrl_y_laxis() * ANALOG_SPEED * time_delta_time();
	forward.z *= ctrl_y_laxis() * ANALOG_SPEED * time_delta_time();
	
	right.x *= ctrl_x_laxis() * ANALOG_SPEED * time_delta_time();
	right.y *= ctrl_x_laxis() * ANALOG_SPEED * time_delta_time();
	right.z *= ctrl_x_laxis() * ANALOG_SPEED * time_delta_time();

	rotation.x -= ctrl_x_raxis() * ANALOG_SPEED * time_delta_time(); 
	rotation.y -= ctrl_y_raxis() * ANALOG_SPEED * time_delta_time(); 
#endif
	
	position.x += forward.x;
	position.y += forward.y;  
	position.z += forward.z; 
	
	position.x += right.x; 
	position.y += right.y; 
	position.z += right.z; 
	
	float yout = position.y; 
	
	get_lvl = (position.y < 48.0f ? 1 : 0);

	ct = mesh_collision(&yout, &position, &collision_mesh[get_lvl]);
	//yout -= 0.0f;
	if(ctrl_button(BTN_A))
		position.y += 1.0f;
		
	position.y = ff_lerp(position.y, yout, 7.0f * time_delta_time());
	
	//printf("Plyaer {%f, %f, %f}\n", position.x, yout, position.z);	
	//printf("rotation {%f, %f, %f}\n", rotation.x, rotation.y, rotation.z);
	if (ct)
	{
		lastPos = position; 
	}else 
	{
		position = lastPos; 
	}	

	render_cameraf(position.x, position.y+15.0f, position.z, rotation.x, rotation.y, rotation.z); 
	
	if (lookat_timer > time_get_tick())
	{
		//printf("tick tick = %d\n", time_get_tick());
		
		switch(lookat_door)
		{
			case 0: 
				render_cameraf(-19.0f, 15.0f, 257.0f, -24.0f, 11.0f, 0.0f);
				break;
			case 1: 
				render_cameraf(-20.1f, 15.0f, 507.8f, -33.9f, 6.6f, 0.0f);
				break;
			case 2: 
				render_cameraf(-33.9f, 120.0f, -121.0f, -313.1f, 7.0f, 0.0f);
				break;
		}
	}
	
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
   //render_aabb(&box);
}

int player_get_lvl()
{
	return get_lvl; 
}

void player_push_back(vec4_t push)
{
	position.x += push.x; 
	position.y += push.y; 
	position.z += push.z; 
}

void player_lookat_door(int i)
{
	lookat_door = i; 
	lookat_timer = LOOKAT_DOOR_AMOUNT + time_get_tick();
	printf("called = %d\n", lookat_timer);
}

aabb_t* player_get_aabb()
{
	return &box; 
}
 
vec4_t* player_get_pos()
{
	return &position; 
}
