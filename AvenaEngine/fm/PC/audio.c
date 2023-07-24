#include "../audio.h" 
#include <SDL2/SDL.h>

#define MAX_SFX 10

SDL_AudioDeviceID dev_music;  //for bg music
SDL_AudioSpec wav_spec; 
Uint32 wav_len; 
Uint8* wav_buff;

SDL_AudioDeviceID dev_sfx; //for sfx
SDL_AudioSpec sfx_spec; 
int sfx_select = 0; 
Uint32 sfx_len[MAX_SFX]; 
Uint8* sfx_buff[MAX_SFX];

void audio_init()
{
	/*nothing to init in SDL2*/
	dev_sfx = SDL_OpenAudioDevice(NULL, 0, &sfx_spec, NULL, 0);
}
 
void audio_update()
{
	Uint32 q = SDL_GetQueuedAudioSize(dev_music);

	if (q <= wav_len)
	{
		SDL_QueueAudio(dev_music, wav_buff, wav_len);
		SDL_PauseAudioDevice(dev_music, 0); 
	}
}

void audio_quit()
{
	SDL_CloseAudioDevice(dev_music);
	SDL_CloseAudioDevice(dev_sfx); 
	SDL_FreeWAV(wav_buff);
}

int audio_load_track(char* file)
{
	if (SDL_LoadWAV(file, &wav_spec, &wav_buff, &wav_len)==NULL)
	{
		printf("audio file not found\n %s", SDL_GetError());
		return -1; 
	}
	
	dev_music = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
	
	/*queue twice for perfect loop*/ 
	SDL_QueueAudio(dev_music, wav_buff, wav_len);
	SDL_QueueAudio(dev_music, wav_buff, wav_len);
	SDL_PauseAudioDevice(dev_music, 0); 
	
	return 0; 
}

void audio_play_track(int track, int loop)
{
	/*useless */
}

int audio_load_sfx(char* file)
{
	if (SDL_LoadWAV(file, &sfx_spec, &sfx_buff[sfx_select], &sfx_len[sfx_select])==NULL)
	{
		printf("audio file not found\n %s", SDL_GetError());
		return -1; 
	}
	
	sfx_select++; 
	return (sfx_select-1); 
}

void audio_play_sfx(int track)
{
	SDL_QueueAudio(dev_sfx, sfx_buff[track], sfx_len[track]);
	SDL_PauseAudioDevice(dev_sfx, 0); 
}
