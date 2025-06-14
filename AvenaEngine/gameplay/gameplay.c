#include "gameplay.h" 
#include "../fw.h" 
#include "../modes.h"

#include "player.h" 
#include "road.h" 
#include "ui.h"
#include "door.h"
#include "switch.h"
#include "ghost.h" 

void gameplay_init()
{
	road_init(); 
	player_init(); 
	
	doors_init();
	switchs_init();
	ghosts_init();
	//cheese_init();
	//cats_init();
	//ui_init();
	
	//chest_player(&player_get_obj()->pos, &player_get_obj()->box, &player_get_obj()->rot.z); 
	//cats_player(&player_get_obj()->box);
	
	/*FUCKING FIX THIS SHIT*/
	//cheese_set_placements(cats_get_placements(), MAX_CATS);
	//printf("CP = %f\n", cats_get_placements()[0].x); 
	//chest_init();
}

void gameplay_start()
{
	player_start(); 
	//player_update();//update once to disable aabb flag
	doors_start();
	ghosts_start();
	switchs_start();
	//cheese_start(); 
	//cats_update();
	//ui_start();
}

void gameplay_update()
{
	player_update(); 
	road_update(); 
	doors_update();
	switchs_update();
	ghosts_update();
	//cheese_update();
	//cats_update(); 
	//ui_update();
	
	//printf(" CAT = %f]\n", vv_sqr_distance(&player_get_obj()->pos, get_placements())); 
} 

void gameplay_render()
{
	render_begin(); 
		//render_draw(road_get_obj()); 	
		
		//render_tpmt_draw(road_get_mt());
		render_draw_mt(road_get_mt());
		//render_tp_md2(player_get_objmd2());
		
		/*CHANGE THIS TO MD2 FOR ANIMATIONS LATER*/
		
	//render_tp_draw(player_get_obj());
	
		for(int i = 0; i < MAX_SWITCHS; ++i)
			render_draw(switchs_get_obj(i));
			
		for(int i = 0; i < MAX_DOORS; ++i)
			render_draw(doors_get_obj(i));
			
			player_reset();
			
		for(int i = 0; i < MAX_GHOSTS; ++i)
			render_draw(ghosts_get_obj(i));
		
		//for(int i = 0; i < MAX_CATS; ++i)
			//render_tp_draw(cats_get_obj(i));

		// HEARTS
		//for(int i = 0; i < MAX_CHEESES; ++i)
			//render_ui_draw(ui_cheese_render(i)); 
/*
		// CHESTS
		for(int j = 0; j < MAX_CHESTS; ++j)
			render_ui_draw(ui_chests_render(j)); 

		for(int i = 0; i < MAX_CHEST; ++i)
			render_draw(chest_get_obj(i));
		*/
		
		//render_tp_draw(cheese_get_obj());
		//render_draw(cat_get_obj()); 
		 
	render_end(); 
}
