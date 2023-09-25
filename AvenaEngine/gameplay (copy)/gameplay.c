#include "gameplay.h" 
#include "../fw.h" 
#include "../modes.h"

#include "player.h" 
#include "road.h" 
#include "ui.h"
#include "chest.h"
#include "spikeroll.h"
#include "ui.h"

void gameplay_init()
{
	player_init(); 
	road_init(); 
	chest_init();
	spikeroll_init();
	ui_init();
	
	chest_player(&player_get_obj()->pos, &player_get_obj()->box, &player_get_obj()->rot.z); 
	spikeroll_player(&player_get_obj()->box);
}

void gameplay_start()
{
	player_start(); 
	player_update();//update once to disable aabb flag
	chest_start(); 
	spikeroll_update();
	ui_start();
}

void gameplay_update()
{
	player_update(); 
	road_update(); 
	chest_update();
	spikeroll_update(); 
	ui_update();
} 

void gameplay_render()
{
	render_begin(); 
		render_draw(road_get_obj()); 	
		render_lerp_md2(player_get_obj());
		
		for(int i = 0; i < MAX_SPIKEROLL; ++i)
			render_draw(spikeroll_get_obj(i));

		// HEARTS
		for(int i = 0; i < MAX_HEARTS; ++i)
			render_ui_draw(ui_hearts_render(i)); 
		// CHESTS
		for(int j = 0; j < MAX_CHESTS; ++j)
			render_ui_draw(ui_chests_render(j)); 

		for(int i = 0; i < MAX_CHEST; ++i)
			render_draw(chest_get_obj(i)); 
	render_end(); 
}
