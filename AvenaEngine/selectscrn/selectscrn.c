#include "selectscrn.h"
#include "../fm/pngloader.h"
#include "../fw.h"
#include "../modes.h"

obj_t thankyou;
mesh_t thankyou_model;


void selectscrn_init()
{

    load_mesh("Assets/bg.obj", &thankyou_model);
    load_png_texture("Assets/thankyou.png", &thankyou.texture);

    obj_init(&thankyou);

    thankyou.model = &thankyou_model;
    thankyou.sca.x = 0.85f; 
	thankyou.sca.y = 0.65f; 
	thankyou.pos.z = -1.5f;
	thankyou.rot.x = 90.0f;
	
}

void selectscrn_start()
{

}
 
void selectscrn_update()
{
	if (ctrl_button_down(BTN_A))
	{
		mode_change(MODE_GAMEPLAY);
	}
}
 
void selectscrn_render()
{
    render_begin();
    	render_ui_draw(&thankyou);
    render_end();
}
