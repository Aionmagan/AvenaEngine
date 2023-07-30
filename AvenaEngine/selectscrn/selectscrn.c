#include "selectscrn.h"
#include "../fm/pngloader.h"
#include "../fw.h"
#define MAX 100
#define INIT 0
#define START 1

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

    // load_mesh("Assets/bg.obj", &modelStoryOne);
	// load_png_texture("Assets/introStory/1.png", &storyOne.texture); 

	// obj_init(&storyOne);
	// storyOne.model = &modelStoryOne;
    // storyOne.sca.x = 0.6f; 
	// storyOne.sca.y = 0.5f; 
	// storyOne.sca.z = 0.1f;
    // storyOne.pos.y = -0.85f;
	// storyOne.pos.z = -1.0f;
    // storyOne.rot.x = -30;

    // load_mesh("Assets/bg.obj", &modelStoryTwo);
	// load_png_texture("Assets/introStory/2.png", &storyTwo.texture); 

    // obj_init(&storyTwo);
	// storyTwo.model = &modelStoryTwo;
    // storyTwo.sca.x = 0.6f; 
	// storyTwo.sca.y = 0.5f; 
	// storyTwo.sca.z = 0.1f;
    // storyTwo.pos.y = -1.60f;
	// storyTwo.pos.z = -1.0f;
    // storyTwo.rot.x = -30;

    // load_mesh("Assets/bg.obj", &modelStoryThree);
	// load_png_texture("Assets/introStory/3.png", &storyThree.texture); 

    // obj_init(&storyThree);
	// storyThree.model = &modelStoryThree;
    // storyThree.sca.x = 0.0f; 
	// storyThree.sca.y = 0.0f;  
	// storyThree.sca.z = 0.1f;
	// storyThree.pos.z = -2.0f;

}

void selectscrn_start()
{

}
 
void selectscrn_update()
{

    if(title.sca.y < 0.3f & section == INIT){
        title.sca.x = title.sca.x + 0.03f; 
	    title.sca.y = title.sca.y + 0.02f;
    }


    if (ctrl_button_down(D_RIGHT) & section == INIT)
	{
        section = START;

        load_mesh("Assets/bg.obj", &modelTitle);
		load_png_texture("Assets/introStory/intro.png", &title.texture);
        obj_init(&title);

        title.model = &modelTitle;

        title.sca.x = 0.6f; 
        title.sca.y = 0.5f; 
        title.sca.z = 0.1f;
        title.pos.y = -0.85f;
        title.pos.z = -1.0f;
	}

    // char buf[MAX];
  
    // gcvt(title.pos.y, 6, buf);
  
    // printf("buffer is: %s\n", buf);

    if(title.pos.y >= -0.85f & title.pos.y < 1.0 & section == START){
        title.pos.y = title.pos.y + 0.0015f;
    }

    

    // if(storyTwo.pos.y > -0.85f && storyTwo.pos.y < -0.40){
        

    //     storyOne.pos.y = storyOne.pos.y + 0.0007f;

    //     storyTwo.pos.y = storyTwo.pos.y + 0.0009f;
    //     storyTwo.sca.x = storyTwo.sca.x - 0.0002f;
    //     storyTwo.rot.x = storyTwo.rot.x - 0.03;




    // }else if(storyTwo.pos.y > -0.85f & storyTwo.pos.y <= 0.56f){
    //     storyOne.pos.y = storyOne.pos.y + 0.0006f;
    //     storyTwo.pos.y = storyTwo.pos.y + 0.0007f;

    //     char buf[MAX];
  
    //     gcvt(storyTwo.pos.y, 6, buf);
  
    //     printf("buffer is: %s\n", buf);

    // }else if(storyTwo.pos.y < 0.56f){
    //     storyTwo.pos.y = storyTwo.pos.y + 0.0009f;

    //     storyOne.pos.y = storyOne.pos.y + 0.0009f;
    //     storyOne.sca.x = storyOne.sca.x - 0.0002f;
    //     storyOne.rot.x = storyOne.rot.x - 0.03;
    // }
    // else{

    //     if(storyThree.sca.x < 0.9f && storyThree.sca.y < 0.6f){
    //         storyThree.sca.x = storyThree.sca.x + 0.1f; 
	//         storyThree.sca.y = storyThree.sca.y + 0.1f;
    //     }
        
    // }

}
 
void selectscrn_render()
{
    render_begin();
    // render_ui_draw(&storyOne);
    // render_ui_draw(&storyTwo);
    // render_ui_draw(&storyThree);
    render_ui_draw(&title);
    render_end();
}
