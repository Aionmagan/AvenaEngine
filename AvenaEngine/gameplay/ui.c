#include "ui.h"
#include "../fm/pngloader.h"
#include "../fw.h"
#include "../modes.h"
#include <stdio.h>

int cheese_select = 0;//MAX_CHEESES-1;

obj_t cheeses[MAX_CHEESES]; 
mesh_t model_ui;
tex_t texhearts;
tex_t texheartsblack; 


void ui_init()
{
    load_mesh("Assets/uicheese.obj", &model_ui);
	load_png_texture("Assets/heart_ui.png",&texhearts); 
	load_png_texture("Assets/heart_ui_black.png",&texheartsblack);

// hearts
    for(int i = 0; i < MAX_CHEESES; i++){
	obj_init(&cheeses[i]);
	cheeses[i].model = &model_ui;
    //cheeses[i].texture = cheese_get_obj()->texture;
    cheeses[i].sca.x = 0.02f; 
	cheeses[i].sca.y = 0.02f; 
	cheeses[i].sca.z = 0.02f;
    cheeses[i].pos.x = -0.24f;//+((i*0.2f)*0.24f); //
    cheeses[i].pos.y = -0.17f + (i*0.08);
	cheeses[i].pos.z = -0.50f;
	cheeses[i].dens = 0.0f;
    }


}
 
void ui_start()
{
	if(cheese_select < 0)
	{
		mode_change(MODE_SELECTSCRN);
	}	
}

void ui_update()
{
    for(int i = 0; i < MAX_CHEESES; i++){
    	cheeses[i].rot.y += 15.0f * time_delta_time();
    }
}

void ui_chest_taken()
{

}

void ui_cheese_taken()
{
	//cheeses[cheese_select].texture = texheartsblack; 
	cheeses[cheese_select].dens = 1.0f; 
	cheese_select++; 
	
	if (cheese_select >= MAX_CHEESES - 1)
		cheese_select = MAX_CHEESES - 1; 
}

void ui_cheese_reset()
{
	for(int i = 0; i < MAX_CHEESES; i++){
    	cheeses[i].dens = 0.0f; 
    }
    cheese_select = 0; 
}

// returns hearts
obj_t* ui_cheese_render(int i)
{
    return &cheeses[i];
}
