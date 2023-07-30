#include "fw.h" 
#include "modes.h" 

#include "selectscrn/selectscrn.h"
#include "gameplay/gameplay.h" 
#include "mainmenu/mainmenu.h"

int main(int argc, char** argv)
{
	int q = 1; 
	float fps = 1000/30.0f; 
	float delta_time = 0; 
	unsigned int start, start1, now = 0; 
	float fpsc = 0; 
	
	render_init(45.0f, 0.1f, 1000.0f);
	audio_init(); 
	ctrl_init(); 
	time_init(); 
	
	//render_bg_color(34, 75, 134); 
	//render_bg_color(0, 75, 134);
	render_bg_color(0,0,0);
	
 	//menu_init();
	//mode_init(); 
	selectscrn_init(); 
	gameplay_init(); 
	audio_load_track("Assets/BGM1.wav"); 
	audio_play_track(1, 1); 
	
	while(q)
	{
		now = time_get_tick(); 
		fpsc = (now-start); 
		
		if (fpsc > fps)
		{	
			start = now; 
			
			audio_update();
			ctrl_update();
			time_update(); 
		
			if (ctrl_event_quit() || ctrl_button(BTN_START)) {q = 0;} 
		
		//start1 = now; 
		now = time_get_tick(); 
		
		//fpsc = 1.0f / (now-start)*1000.0f; 
		
		//fpsc = 1000.0f / (now-start1); 
		//printf("FPS = %f\n", fpsc);
		//fpsc = (now-start); 
		
		//fpsc = (now-start)*1000.0f; 
		//delta_time = (now - start);
		//printf("delta_time = %f\n", delta_time);
		//printf("FPS = %f | fps = %f\n", fpsc, fps);
		//if (fpsc > fps)
		//{		
			
			//switch(mode_get())
			switch(1)
			{
				case MODE_SELECTSCRN:
					if (mode_one_call())
						selectscrn_start(); 
						 
					selectscrn_update(); 
					selectscrn_render(); 
					break; 
				case MODE_GAMEPLAY: 
					if (mode_one_call())
						gameplay_start(); 
						
					gameplay_update(); 
					gameplay_render(); 
					break; 
				case MODE_MAINMENU:
					menu_update(); 
					menu_render(); 
					break;
				default:break; 
			}
		}
	}
	
	audio_quit(); 
	render_quit();
	 
	return 0;  
}
