#include "door.h"

#include "../fw.h"
#include "../fm/timer.h"
#include "../fm/obj.h" 
#include "../modes.h"

#include "player.h"

#define MAX_KEYS_DOOR_1 2
#define MAX_KEYS_DOOR_2 5
#define MAX_KEYS_EXIT 6

unsigned int door_keys = 0; 

/*AABB stuff*/
vec4_t s_pos_1; 
vec4_t s_pos_2; 
vec4_t s_pos_3; 

vec4_t s_sca_1; 
vec4_t s_sca_2; 
vec4_t s_sca_3; 

/*exit door*/
aabb_t s_aabb_exit; 
vec4_t s_pos_exit; 
vec4_t s_sca_exit; 

mesh_t door_mesh; 
tex_t door_tex; 

obj_t door1;
obj_t door2; 
obj_t door3; 

vec4_t door1_star_pos={0};
vec4_t door2_star_pos={0};
vec4_t door3_star_pos={0};

int door1_open = 0; 
int door2_open = 0; 
int door3_open = 0; 

//player's box 
aabb_t* player_box; 

void doors_init()
{
	load_mesh("Assets/door.obj", &door_mesh);
	load_png_texture("Assets/doors.png", &door_tex);
	obj_init(&door1);
	obj_init(&door2);
	obj_init(&door3);
	
	door1.model = &door_mesh;
	door2.model = &door_mesh;
	door3.model = &door_mesh;
	
	door1.texture = door_tex;
	door2.texture = door_tex;
	door3.texture = door_tex;
	
	door1_star_pos.x = -0.0f; 
	door1_star_pos.z = 148.0f;
	door1.pos = door1_star_pos; 
	
	s_pos_1.x = door1.pos.x;
	s_pos_1.y = door1.pos.y+10.0f;
	s_pos_1.z = door1.pos.z;
	
	s_sca_1.x = 25.0f; 
	s_sca_1.y = 10.0f; 
	s_sca_1.z = 15.0f; 
	
	s_pos_exit.x = -100.0f;
	s_pos_exit.y =  115.0f; 
	s_pos_exit.z = -190.0f; 
	
	s_sca_exit.x = 25.0f; 
	s_sca_exit.y = 10.0f; 
	s_sca_exit.z = 10.0f; 
	
	aabb_init(&s_aabb_exit, &s_pos_exit, &s_sca_exit); 

	aabb_init(&door1.box, &s_pos_1, &s_sca_1);
	
	door2_star_pos.x = 40.0f; 
	door2_star_pos.z = 450.0f;
	door2.pos = door2_star_pos;
	door2.rot.y = 90.0f;
	
	s_pos_2.x = door2.pos.x;
	s_pos_2.y = door2.pos.y+10.0f;
	s_pos_2.z = door2.pos.z;
	
	s_sca_2.x = 15.0f; 
	s_sca_2.y = 10.0f; 
	s_sca_2.z = 25.0f; 
	
	aabb_init(&door2.box, &s_pos_2, &s_sca_2);
	
	
	door3_star_pos.x = -100.0f; 
	door3_star_pos.y =  105.0f;
	door3_star_pos.z = -180.0f;
	door3.pos = door3_star_pos;
	//door3.rot.y =  105.0f;
	
	s_pos_3.x = door3.pos.x;
	s_pos_3.y = door3.pos.y+10.0f;
	s_pos_3.z = door3.pos.z;
	
	s_sca_3.x = 25.0f; 
	s_sca_3.y = 10.0f; 
	s_sca_3.z = 15.0f; 
	
	aabb_init(&door3.box, &s_pos_3, &s_sca_3);
	
	player_box = player_get_aabb();
}

void doors_start()
{
	door1_open = 0; 
	door2_open = 0; 
 	door3_open = 0; 
 	
 	door1.pos = door1_star_pos; 
 	door2.pos = door2_star_pos; 
 	door3.pos = door3_star_pos; 
 	
 	door1.box.is_active = 1; 
 	door2.box.is_active = 1; 
 	door3.box.is_active = 1; 
}

void doors_update()
{
	//printf("Player_box {%f, %f, %f}\n", player_box->min.x, player_box->min.y, player_box->min.z);
	s_pos_1.x = door1.pos.x;
	s_pos_1.y = door1.pos.y+10.0f;
	s_pos_1.z = door1.pos.z;
	aabb_update(&door1.box, &s_pos_1, &s_sca_1);
	
	s_pos_2.x = door2.pos.x;
	s_pos_2.y = door2.pos.y+10.0f;
	s_pos_2.z = door2.pos.z;
	aabb_update(&door2.box, &s_pos_2, &s_sca_2);
	
	s_pos_3.x = door3.pos.x;
	s_pos_3.y = door3.pos.y+10.0f;
	s_pos_3.z = door3.pos.z;
	aabb_update(&door3.box, &s_pos_3, &s_sca_3);
	
	//aabb_update(&s_aabb_exit, &s_pos_exit, &s_sca_exit); 
	
	if (aabb_overlap(&door1.box, player_box))
	{
		vec4_t dir={0};
		dir.z = 5.0f;
		
		player_push_back(dir);
	}
	
	if (aabb_overlap(&door2.box, player_box))
	{
		vec4_t dir={0};
		dir.x = -5.0f;
		
		player_push_back(dir);
	}
	
	if (aabb_overlap(&door3.box, player_box))
	{
		vec4_t dir={0};
		dir.z = 5.0f;
		
		player_push_back(dir);
	}
	
	if (aabb_overlap(&s_aabb_exit, player_box))
	{
		printf("thank you for playing");
		mode_change(MODE_SELECTSCRN);
	}
	
	if (door1_open)
	{
		if (door1.pos.x > -48.0f)
			door1.pos.x -= 7.0f * time_delta_time();
		else 
			door1.box.is_active = 0;  
		//printf("door1.pos {%f, %f, %f}\n", door1.pos.x, door1.pos.y, door1.pos.z);
	}
	
	if (door2_open)
	{
		if (door2.pos.z < 498.0f)
			door2.pos.z += 7.0f * time_delta_time(); 
		else 
			door2.box.is_active = 0; 
		//printf("door2.pos {%f, %f, %f}\n", door2.pos.x, door2.pos.y, door2.pos.z);
	}
	
	if (door3_open)
	{
		if (door3.pos.x > -140.0f)
			door3.pos.x -= 7.0f * time_delta_time(); 
		else 
			door3.box.is_active = 0; 
		//printf("door3.pos {%f, %f, %f}\n", door3.pos.x, door3.pos.y, door3.pos.z);
	}
	
#if 0//defined(__DEBUG__)	
	aabb_hit(&door1.box, player_box);
	aabb_hit(&door2.box, player_box);
	aabb_hit(&door3.box, player_box);
	
	if (ctrl_button(BTN_A))
		door1_open = 1; 
	if (ctrl_button(BTN_B))
		door2_open = 1;
	if (ctrl_button(BTN_X))
		door3_open = 1;
#endif
}

void doors_get_player()
{

}

void doors_open(int i)
{
	switch(i)
	{
		case 0: 
			door1_open = 1;
			break;
		case 1: 
			door2_open = 1;
			break;
		case 2: 
			door3_open = 1;
			break;
		default:break;
	}
}

obj_t* doors_get_obj(int i)
{
	//render_aabb(&s_aabb_exit);
	switch(i)
	{
		case 0: 
			return &door1;
		case 1: 
			return &door2;
		case 2: 
			return &door3;
		default:break;
	}
}

