#ifndef __AUDIO_H__
#define __AUDIO_H__

void audio_init(); 
void audio_update(); 
void audio_quit(); 
int audio_load_track(char* file); 
void audio_play_track(int track, int loop);
int audio_load_sfx(char* file); 
void audio_play_sfx(int track); 

#endif//__AUDIO_H__
