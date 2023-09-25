#include "mainmenu.h" 
#include "../fw.h"
#include "../fm/timer.h"
#include "../fm/pngloader.h"
#include <math.h>

/*
mesh_t mesh_test; 
obj_t obj_test; 

mesh_t mesh_player; 
obj_t  obj_player;

vec4_t pos; 
vec4_t rot; 
vec4_t lastPos; 
	
	
float cccspeed = 17.0f; 
*/
/*float area(float x1, float y1, float x2, float y2, float x3, float y3)
{
	return fabsf((x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2))/2.0f);//*0.5f); 
	//return abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0);
}*/

/*public static bool PointInTriangle(Point p, Point p0, Point p1, Point p2)
{
    var s = (p0.X - p2.X) * (p.Y - p2.Y) - (p0.Y - p2.Y) * (p.X - p2.X);
    var t = (p1.X - p0.X) * (p.Y - p0.Y) - (p1.Y - p0.Y) * (p.X - p0.X);

    if ((s < 0) != (t < 0) && s != 0 && t != 0)
        return false;

    var d = (p2.X - p1.X) * (p.Y - p1.Y) - (p2.Y - p1.Y) * (p.X - p1.X);
    return d == 0 || (d < 0) == (s + t <= 0);
}*/

/*
int ptInTriangle(vec4_t p, vertex_t p0, vertex_t p1, vertex_t p2) 
{
	//printf("P{%f, %f} | P0{%f, %f} | P1{%f, %f} | P2{%f, %f}\n", p.x, p.z, p0.x, p0.z, p1.x, p1.z, p2.x, p2.z); 
    float A = 0.5f * (-p1.z * p2.x + p0.z * (-p1.x + p2.x) + p0.x * (p1.z - p2.z) + p1.x * p2.z);
    float sign = A < 0 ? -1.0f : 1.0f;
    float s = (p0.z * p2.x - p0.x * p2.z + (p2.z - p0.z) * p.x + (p0.x - p2.x) * p.z) * sign;
    float t = (p0.x * p1.z - p0.z * p1.x + (p0.z - p1.z) * p.x + (p1.x - p0.x) * p.z) * sign;
    
    //printf("A = %f, S = %f, T = %f\n", A, s, t);
    return (s > 0 && t > 0 && (s + t) < 2 * A * sign);
}

int checkTriangles(vec4_t* player)
{
	int A, A1, A2, A3; 
	float r; 
	int i; 
	for(i = 0; i < mesh_test.face_count; ++i)
	{

		//printf("\n player {%f , %f}  |  vertex {%f , %f}\n", player->x, player->z,
//		mesh_test.verts[mesh_test.faces[i].vx].x,
	//	mesh_test.verts[mesh_test.faces[i].vx].z);
		A = ptInTriangle(*player, 
		    mesh_test.verts[mesh_test.faces[i].vx],
		    mesh_test.verts[mesh_test.faces[i].vy],
		    mesh_test.verts[mesh_test.faces[i].vz]);
		    
		//printf("A = %d\n", A);
		if (A)
			return 1; 	       		
			
		//printf("called \n");
	}
	
	return 0; 				    
}
*/

void menu_init()
{
/*	render_bg_color(100,80,20);
	
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

void menu_update()
{
/*	float s = cccspeed * 0.2f;// * time_delta_time(); 	
	int ct = 0; 
	
	if (!ctrl_button(BTN_Y))
	{			
		obj_player.pos.z += ctrl_y_axis() * s; 
		obj_player.pos.x += ctrl_x_axis() * s; 
		
	    if (ctrl_x_axis() != 0 || ctrl_y_axis() != 0)
		{
			float r = atan2(ctrl_x_axis(), ctrl_y_axis())*180/3.14159;
			obj_player.rot.y = r-180.0f; 
		}
		
		ct = mesh_collision(&obj_player.pos, &mesh_test);
		pos.z = obj_player.pos.z + 47.0f; 
		pos.x = obj_player.pos.x; 
		if (ct)
		{
			lastPos = obj_player.pos; 
		}else 
		{
			obj_player.pos = lastPos; 
		}	
		
		
	}else
	{
		if (ctrl_button(BTN_B))
		{
			pos.y -= ctrl_y_axis() * s; 
		}else
		{
			pos.z = (obj_player.pos.z+47.0f) + ctrl_y_axis() * 12.0f;
		}
		
		pos.x = (obj_player.pos.x)+ctrl_x_axis() * 12.0f;  
		
		if (ctrl_button(BTN_A))
			rot.y -= s; 
		if (ctrl_button(BTN_X))
			rot.y += s;  
	}	
	
	//obj_test.box.hit = (ct > 0.0f) ? 1 : 0;
//	if (ctrl_button(BTN_Y))
	//	pos.y += cspeed; 
//	if (ctrl_button(BTN_B))
		//pos.y -= cspeed; 
	//printf("ct = %f\n", ct); 
	//printf("pos = {%f, %f, %f}, rot {%f, %f, %f}\n", pos.x, pos.y, pos.z, rot.x, rot.y, rot.z); 
	
	render_cameraf(pos.x, pos.y, pos.z, rot.x, rot.y, rot.z); 
	*/
}

void menu_render()
{
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
