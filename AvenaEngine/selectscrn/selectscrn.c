#include "selectscrn.h"
#include "../fm/pngloader.h"
#include "../fw.h"
#include "../modes.h"
#define MAX 100
#define INIT 0
#define TRANSITION 1
#define START 2

// obj_t storyOne; 
// mesh_t modelStoryOne;

// obj_t storyTwo; 
// mesh_t modelStoryTwo;

// obj_t storyThree; 
// mesh_t modelStoryThree;

obj_t title;
mesh_t modelTitle;

int section = INIT;


void selectscrn_init()
{

    load_mesh("Assets/bg.obj", &modelTitle);
    load_png_texture("Assets/introStory/title.png", &title.texture);

    obj_init(&title);

    title.model = &modelTitle;
    title.sca.x = 0.0f; 
	title.sca.y = 0.0f; 
	title.pos.z = -1.0f;

}

void selectscrn_start()
{

}
 
void selectscrn_update()
{

    if(section == INIT & title.sca.y < 0.41f){
        title.sca.x = title.sca.x + 0.028f; 
	    title.sca.y = title.sca.y + 0.02f;
    }


    if (section == INIT && ctrl_button_down(BTN_A))
	{
		printf("hello");
        section = TRANSITION;
		//if (title.texture)
		audio_load_track("Assets/va.wav"); 
		audio_play_track(2, 1); 
        //load_mesh("Assets/bg.obj", &modelTitle);
    }

    if(section == TRANSITION & title.sca.y >= 0.0f & title.sca.x >= 0.0f){
        title.sca.x = title.sca.x - 0.028f; 
	    title.sca.y = title.sca.y - 0.02f;
    }else if(section == TRANSITION & title.sca.y <= 0.0f & title.sca.x <= 0.0f){

		load_png_texture("Assets/introStory/intro.png", &title.texture);
        obj_init(&title);

        title.model = &modelTitle;

        title.sca.x = 0.6f; 
        title.sca.y = 0.5f; 
        title.sca.z = 0.1f;
        title.pos.y = -0.85f;
        title.pos.z = -1.0f;

        section = START;
    }

	if(section == START)
    {
    	if(title.pos.y >= -0.85f && title.pos.y < 1.0){
    	    title.pos.y = title.pos.y + 0.0020f;
    	}else
   	 	{
			mode_change(MODE_GAMEPLAY);
			audio_load_track("Assets/BGM1.wav"); 
			audio_play_track(1, 1);  
   	 	}

        if(ctrl_button_down(BTN_A))
        {
            mode_change(MODE_GAMEPLAY);
			audio_load_track("Assets/BGM1.wav"); 
			audio_play_track(1, 1); 
        }
	}
    // char buf[MAX];
  
    // gcvt(title.pos.y, 6, buf);
  
    // printf("buffer is: %s\n", buf);

    // if(section == START & title.pos.y >= -0.85f & title.pos.y < 1.0){
    //     title.pos.y = title.pos.y + 0.0020f;
    // }else
   	//  	{
	// 		mode_change(MODE_GAMEPLAY);
	// 		audio_load_track("Assets/BGM1.wav"); 
	// 		//audio_play_track(2, 2);  
   	//  	}

}
 
void selectscrn_render()
{
    render_begin();
    render_ui_draw(&title);
    render_end();
}
