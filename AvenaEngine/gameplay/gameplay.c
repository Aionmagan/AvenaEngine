#include "gameplay.h" 
#include "../fw.h" 
#include "../modes.h"

#include "player.h" 
#include "road.h" 
#include "ui.h"

obj_t panel; 
mesh_t model; 

void gameplay_init()
{
	player_init(); 
	road_init(); 
	//ui_init(); 
	
	load_mesh("Assets/bg.obj", &model);
	load_png_texture("Assets/fire.png", &panel.texture); 
	
	obj_init(&panel);
	panel.model = &model;
	panel.sca.x = 0.4f; 
	panel.sca.y = 0.4f; 
	panel.sca.z = 0.4f; 
	panel.pos.z = -1.0f;
	//panel.pos.y = 3.0f; 
	//panel.rot.x = 90.0f;
	//panel.rot.z = 180.0f;  
}

void gameplay_start()
{
	player_start(); 
	player_update();//update once to disable aabb flag
	//ui_start();
}

void gameplay_update()
{
	//if (ctrl_button_down(B)||player_get_obj()->box.hit)
		//mode_change(MODE_MAINMENU);
		//panel.pos.z = 100.0f*sinf(time_get_tick()); 
		panel.rot.z = 180.0f*sinf((time_get_tick()*0.001f)); 
		
		//panel.pos.x = player_get_obj()->pos.x; 
	player_update(); 
	road_update(); 
	//ui_update();
} 

void gameplay_render()
{
	render_begin(); 
		render_draw(road_get_obj()); 	
		render_lerp_md2(player_get_obj());
		
		//render_ui_draw(&panel); 
		//render_tp_draw(&panel);
		//render_ui_draw(ui_render()); 
		//render_bb_draw(&panel);
	render_end(); 
}
