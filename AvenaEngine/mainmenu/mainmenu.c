#include "mainmenu.h" 
#include "../fw.h"
#include "../fm/timer.h"
#include "../fm/pngloader.h"
#include "../modes.h"
#include <math.h>

#define DEAD_COUNT 2000

mesh_t dead_mesh; 
obj_t dead_obj; 
long timer; 

void menu_init()
{

	load_mesh("Assets/bg.obj", &dead_mesh);
	load_png_texture("Assets/youdead.png", &dead_obj.texture);
	
	obj_init(&dead_obj);
	
	dead_obj.model = &dead_mesh; 
	dead_obj.rot.x = 90.0f;
	dead_obj.pos.z = -1.5f;
	dead_obj.sca.x = 0.85f; 
	dead_obj.sca.y = 0.65f;
	//render_bg_color(100,80,20);
/*	
	load_mesh("Assets/meshCollider.obj", &mesh_test);
	load_png_texture("Assets/Hall_Test.png", &obj_test.texture);
	
	load_mesh("Assets/rat.obj", &mesh_player);
	load_png_texture("Assets/chest.png", &obj_player.texture); 
	
	obj_test.model = &mesh_test; 
	obj_player.model = &mesh_player; 
	
	obj_init(&obj_test);
	obj_test.box.is_active = 0; 
	pos.y = 82.0f; 
	pos.z = 60.0f; 
	rot.y = -60.0f; 
	
	obj_init(&obj_player);
	obj_player.box.is_active = 0;
	obj_player.pos.x = 13.0f;
	obj_player.pos.y = 3.0f; 
	obj_player.pos.z = 13.0f; 
	lastPos = obj_player.pos; 
	*/
}

void menu_start()
{
	timer = DEAD_COUNT + time_get_tick();
}

void menu_update()
{
	if (timer < time_get_tick())
		mode_change(MODE_GAMEPLAY);
}

void menu_render()
{

	render_begin();
		render_ui_draw(&dead_obj);
	render_end();
/*
	render_begin(); 
		render_draw(&obj_player); 
		render_draw(&obj_test); 
	render_end(); 
	*/
}

/*
int cccheckTriangles(vec4_t* player)
{
	float A, A1, A2, A3; 
	float r; 
	int i; 
	for(i = 0; i < mesh_test.face_count; ++i)
	{
		A = area(mesh_test.verts[mesh_test.faces[i].vx].x,
		         mesh_test.verts[mesh_test.faces[i].vx].z, 
		         mesh_test.verts[mesh_test.faces[i].vy].x,
		         mesh_test.verts[mesh_test.faces[i].vy].z,
		         mesh_test.verts[mesh_test.faces[i].vz].x,
		         mesh_test.verts[mesh_test.faces[i].vz].z
		         );
		         
		A1 = area(player->x, player->z,
		          mesh_test.verts[mesh_test.faces[i].vy].x,
		          mesh_test.verts[mesh_test.faces[i].vy].z,
		          mesh_test.verts[mesh_test.faces[i].vz].x,
		          mesh_test.verts[mesh_test.faces[i].vz].z
		         );
		         
		A2 = area(mesh_test.verts[mesh_test.faces[i].vx].x,
		          mesh_test.verts[mesh_test.faces[i].vx].z, 
		          player->x, player->z,
		          mesh_test.verts[mesh_test.faces[i].vz].x,
		          mesh_test.verts[mesh_test.faces[i].vz].z
		         );	
		         
		A3 = area(mesh_test.verts[mesh_test.faces[i].vx].x,
		          mesh_test.verts[mesh_test.faces[i].vx].z, 
		          mesh_test.verts[mesh_test.faces[i].vy].x,
		          mesh_test.verts[mesh_test.faces[i].vy].z,
		          player->x, player->z
		         );		      
		         
		printf("\nct = %f | %f\n", A1 + A2 + A3, A);
		printf("\n A = %f, A1 = %f, A2 = %f, A3 = %f\n", A, A1, A2, A3); 
		//printf("\n player {%f , %f}  |  vertex {%f , %f}\n", player->x, player->z,
//		mesh_test.verts[mesh_test.faces[i].vx].x,
	//	mesh_test.verts[mesh_test.faces[i].vx].z);
		
		r = (A1+A2+A3);  
		if (A == r) return 1;    	       		
	}
	
	return 0; 				    
}
*/
