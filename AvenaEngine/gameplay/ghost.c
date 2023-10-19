#include "ghost.h" 

#include "../fw.h" 
#include "../fm/timer.h"
#include "../fm/obj.h" 
#include "../modes.h"

#include "player.h"

#define GHOST_SPEED 1.0

#define GHOST_NODE_1 7
#define GHOST_NODE_2 6
#define GHOST_NODE_3 8

#define WALK_STATE 0
#define ATTACK_STATE 1

mesh_t ghost_mesh; 
tex_t ghost_tex; 
tex_t ghost_tex1; 
obj_t ghosts[MAX_GHOSTS];

vec4_t ghosts_box_pos[MAX_GHOSTS];
vec4_t ghosts_box_sca; 

vec4_t ghost_target={0};
vec4_t ghost_fwrd={0};
vec4_t fwrd_vec={0.0f, 0.0f, 1.0f};
vec4_t cnorm={0}; 

int ghost_node_1_select = 1; 
int ghost_node_2_select = 0; 
int ghost_node_3_select = 0; 

int ghost_state[MAX_GHOSTS] = {WALK_STATE};


int gns1 = 1; 
int gns3 = 1; 

aabb_t* player_ghost_box; 

vec4_t ghost_node_1[]=
{
	/*pos(x,y,z) rot y*/
	{-65.0f, 10.0f, 372.0f, 270.0}, 
	{ 1.5f,  10.0f, 372.0f, -90.0f},
	{ 1.5f,  10.0f, 300.0f, 0.0f}, 
	{-65.0f, 10.0f, 300.0f, 90.0f},
	{ 1.5f,  10.0f, 300.0f, -90.0f}, 
	{ 80.0f, 10.0f, 300.0f, -90.0f},
	{ 80.0f, 10.0f, 250.0f, 0.0f},
};

vec4_t ghost_node_2[]=
{
	{-100.0f, 10.0f, -215.0f, -90.0f}, 
	{-100.0f, 10.0f, -45.0f,  180.0f},
	{ 25.0f,  10.0f, -45.0f,  270.0f}, 
	{ 25.0f,  10.0f,  80.0f,  180.0f},
	{-175.0f, 10.0f,  80.0f,   90.0f},
	{-175.0f, 10.0f, -215.0f,  0.0f},
};

vec4_t ghost_node_3[]=
{
	{-175.0f, 115.0f, -150.0f, 0.0f}, 
	{-25.0f,  115.0f, -150.0f, -90.0f},
	{-25.0f,  115.0f, -75.0f, -180.0f}, 
	{-100.0f, 115.0f, -75.0f, -270.0f},
	{-100.0f,  115.0f,  0.0f, -180.0f},
	{-100.0f,  115.0f, -75.0f, 0.0f},
	{-175.0f,  115.0f, -80.0f, 90.0f},
	{-175.0f, 115.0f, -80.0f,  90.0f},
};

void ghosts_init()
{
	load_mesh("Assets/ghost.obj", &ghost_mesh);
	load_png_texture("Assets/ghost1.png", &ghost_tex);
	load_png_texture("Assets/ghost2.png", &ghost_tex1);
	
	ghosts_box_pos[0] = ghost_node_1[0];
	ghosts_box_pos[1] = ghost_node_2[0]; 
	ghosts_box_pos[2] = ghost_node_3[0];
	
	ghosts_box_sca.x = 7.0f;
	ghosts_box_sca.y = 10.0f;
	ghosts_box_sca.z = 7.0f;
	
	for (int i = 0; i < MAX_GHOSTS; ++i)
	{
		obj_init(&ghosts[i]);
		
		ghosts[i].model   = &ghost_mesh;
		ghosts[i].texture = ghost_tex; 
		ghosts[i].pos     = ghosts_box_pos[i]; 
		
		aabb_init(&ghosts[i].box, &ghosts_box_pos[i], &ghosts_box_sca);
	}
	
	player_ghost_box = player_get_aabb();
}

void ghosts_start()
{
	ghost_node_1_select = 0; 
	ghost_node_2_select = 0; 
	ghost_node_3_select = 0; 
	
	ghosts[0].pos = ghost_node_1[ghost_node_1_select];
	ghosts[1].pos = ghost_node_2[ghost_node_2_select];
	ghosts[2].pos = ghost_node_3[ghost_node_3_select];
	
	ghost_state[0] = WALK_STATE;
	ghost_state[1] = WALK_STATE;
	ghost_state[2] = WALK_STATE;
	
	ghosts[0].texture = ghost_tex;
	ghosts[1].texture = ghost_tex;
	ghosts[2].texture = ghost_tex;
}

int ghost_follow_player(vec4_t* ghost_pos, vec4_t* ghost_rot, vec4_t* ghost_node, float distance_from_node, int* ghost_state)
{
	float r = 0.0f; 
	//float d = 0.0f; 
	
	vv_sub(&ghost_target, player_get_pos(), ghost_pos);
	vv_norm(&ghost_target, &ghost_target);
	
	r = RAD2DEG(atan2(ghost_target.x, ghost_target.z))-180.0f;
	
	ghost_rot->y = r; 
	
	r = 48 * GHOST_SPEED * time_delta_time();
	
	ghost_pos->x += ghost_target.x * r;
	ghost_pos->z += ghost_target.z * r;
	
    r = vv_sqr_distance(ghost_pos, ghost_node);
	//d = vv_sqr_distance(ghost_pos, player_get_pos());
	//printf("sqr_distance = %f\n", r);
	if (r > distance_from_node)
	{
		//printf("I'M LEAVING\n");
		*ghost_state = WALK_STATE;
		
		return 1;
	}
	
	return 0;
}

void ghost_1_update()
{
	float gt = GHOST_SPEED * time_delta_time();
	
		/*basement ghost*/
	if (ghost_state[0] == WALK_STATE)
	{
		vv_move_towards(&ghosts[0].pos, &ghosts[0].pos,
			            &ghost_node_1[ghost_node_1_select], gt);
		
		if (gns1 == -1 && ghost_node_1_select != 6)
			ghosts[0].rot.y = ghost_node_1[ghost_node_1_select+1].w+180.0f; 
		else
			ghosts[0].rot.y = ghost_node_1[ghost_node_1_select].w; 
		
		if (vv_distance(&ghosts[0].pos, &ghost_node_1[ghost_node_1_select])<1.0f)
		{
			ghost_node_1_select+=gns1;
			
			if (ghost_node_1_select >= GHOST_NODE_1-1||ghost_node_1_select <= 0)	
				gns1 *= -1; 
		}
	}else 
	{	
		if(ghost_follow_player(&ghosts[0].pos, &ghosts[0].rot,
							 &ghost_node_1[ghost_node_1_select], 
							 40000.0f, &ghost_state[0]))
		{
			ghosts[0].texture = ghost_tex; 
		}

	}
	/*basement ghost*/
}

void ghost_2_update()
{
	float gt = GHOST_SPEED * time_delta_time();
	
	/*lvl2 ghost*/
	if (ghost_state[1] == WALK_STATE)
	{
		vv_move_towards(&ghosts[1].pos, &ghosts[1].pos,
			            &ghost_node_2[ghost_node_2_select], gt);
			            
		ghosts[1].rot.y = ghost_node_2[ghost_node_2_select].w;
			            
		if (vv_distance(&ghosts[1].pos, &ghost_node_2[ghost_node_2_select])<1.0f)
		{
			ghost_node_2_select++;
			
			if (ghost_node_2_select >= GHOST_NODE_2)
				ghost_node_2_select = 0;  
		}   
	}else
	{
		if (ghost_follow_player(&ghosts[1].pos, &ghosts[1].rot,
	  				        &ghost_node_2[ghost_node_2_select], 
							30000.0f, &ghost_state[1]))
		{
			ghosts[1].texture = ghost_tex; 
		}
	}	
	/*lvl2 ghost*/
}

void ghost_3_update()
{
	float gt = GHOST_SPEED * time_delta_time();
	
	/*lvl1 ghost*/
	if (ghost_state[2] == WALK_STATE)
	{
		vv_move_towards(&ghosts[2].pos, &ghosts[2].pos,
			            &ghost_node_3[ghost_node_3_select], gt);
			            
		ghosts[2].rot.y = ghost_node_3[ghost_node_3_select].w;
			            
		if (vv_distance(&ghosts[2].pos, &ghost_node_3[ghost_node_3_select])<1.0f)
		{
			ghost_node_3_select++;
			
			if (ghost_node_3_select >= GHOST_NODE_3-1)
				ghost_node_3_select = 0;  
		}
	}else 
	{
		if (ghost_follow_player(&ghosts[2].pos, &ghosts[2].rot,
	  				        &ghost_node_3[ghost_node_3_select], 
							40000.0f, &ghost_state[2]))
		{
			ghosts[2].texture = ghost_tex; 
		}		
	}  
	/*lvl1 ghost*/
}

void ghosts_update()
{
	float gt = GHOST_SPEED * time_delta_time();
	
	aabb_update(&ghosts[0].box, &ghosts[0].pos, &ghosts_box_sca);
	aabb_update(&ghosts[1].box, &ghosts[1].pos, &ghosts_box_sca);
	aabb_update(&ghosts[2].box, &ghosts[2].pos, &ghosts_box_sca);
	
	aabb_hit(&ghosts[0].box, player_ghost_box);
	aabb_hit(&ghosts[1].box, player_ghost_box);
	aabb_hit(&ghosts[2].box, player_ghost_box);
	
	/*basement ghost*/
	ghost_1_update();
	
	/*lvl2 ghost*/
	ghost_2_update();
	
	/*lvl1 ghost*/
	ghost_3_update();
	
	if (ghosts[0].box.hit || ghosts[1].box.hit || ghosts[2].box.hit)
	{
		mode_change(MODE_MAINMENU);
	}
	
#if 1
	/*check if player is in sight*/
	for(int i = 0; i < MAX_GHOSTS; ++i)
	{
		vv_rot_y(&ghost_fwrd, &fwrd_vec, DEG2RAD(ghosts[i].rot.y)); 
		vv_sub(&cnorm, player_get_pos(), &ghosts[i].pos);
		vv_norm(&cnorm, &cnorm);
					
		float lookat = vv_dot(&cnorm, &ghost_fwrd); 
			
		//printf("look at = %f\n", lookat);
		if (lookat < -0.90f)
		{
			if (vv_sqr_distance(&ghosts[i].pos, 
			    player_get_pos()) < 6500.0f)            
			{
				ghost_state[i] = ATTACK_STATE;
				ghosts[i].texture = ghost_tex1;  
				//player_reset();
				//printf("caught!!\n");
			}
		}
	}	
#endif
}

void ghosts_reset()
{

}

obj_t* ghosts_get_obj(int i)
{
	return &ghosts[i];
}
