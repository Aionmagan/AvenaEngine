#include "ui.h"
#include "../fm/pngloader.h"
#include "../fw.h"
#include <stdio.h>
int chest_select = 0;

obj_t hearts[MAX_HEARTS]; 
mesh_t model_ui;
tex_t texhearts;

obj_t chests[MAX_CHESTS];
//mesh_t modelchests;
tex_t texchests;
tex_t texchestsblack;

void ui_init()
{
    load_mesh("Assets/bg.obj", &model_ui);
	load_png_texture("Assets/heart_ui.png",&texhearts); 
    load_png_texture("Assets/chest_ui_black.png",&texchestsblack); 
    load_png_texture("Assets/chest_ui.png",&texchests); 

// hearts
    for(int i = 0; i < MAX_HEARTS; i++){
	obj_init(&hearts[i]);
	hearts[i].model = &model_ui;
    hearts[i].texture = texhearts;
    hearts[i].sca.x = 0.03f; 
	hearts[i].sca.y = 0.03f; 
	hearts[i].sca.z = 0.1f;
    hearts[i].pos.x = -0.24f+((i*0.2f)*0.24f); //
    hearts[i].pos.y = 0.17f;
	hearts[i].pos.z = -0.50f;
    }
// chests
    for(int j = 0; j < MAX_CHESTS; j++){
	obj_init(&chests[j]);
	chests[j].model = &model_ui;
    chests[j].texture = texchestsblack;
    chests[j].sca.x = 0.02f; 
	chests[j].sca.y = 0.02f; 
	chests[j].sca.z = 0.1f;
    chests[j].pos.x = 0.09f+((j*0.2f)*0.20f); //
    chests[j].pos.y = 0.17f;
	chests[j].pos.z = -0.50f;
    }

}
 
void ui_start()
{

}

void ui_update()
{
    printf("hello\n");
    if (ctrl_button_down(BTN_X))
    {
        ui_chest_taken();
    }
   // hearts.pos.y = storyOne.pos.y + 0.0007f;
}

void ui_chest_taken()
{
    chests[chest_select].texture = texchests;
    chest_select ++;
    if (chest_select > MAX_CHESTS)
        chest_select = MAX_CHESTS;
}
// returns hearts
obj_t* ui_hearts_render(int i)
{
    return &hearts[i];
}

// returns chests
obj_t* ui_chests_render(int j)
{
    return &chests[j];
}