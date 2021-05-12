#include "Audio.h"

Audio::Audio()
{

	if (Mix_Playing(sfx_channel[0]) == 0) {
		Mix_FreeChunk(jump);
	}
	if (Mix_Playing(sfx_channel[1]) == 0) {
		Mix_FreeChunk(trap);
	}
	if (Mix_Playing(sfx_channel[2]) == 0) {
		Mix_FreeChunk(fish);
	}
	if (Mix_Playing(sfx_channel[3]) == 0) {
		Mix_FreeChunk(win);
	}
	if (Mix_Playing(sfx_channel[4]) == 0) {
		Mix_FreeChunk(gameover);
	}
	if (music != NULL) {
		Mix_FreeMusic(music);
	}
	Mix_CloseAudio();
}

Audio::~Audio()
{
}

void Audio::Init()
{
}

void Audio::Update(float deltaTime)
{
}

void Audio::Render()
{
}

void Audio::InitAudio()
{
	

	int flags = MIX_INIT_MP3 | MIX_INIT_FLAC | MIX_INIT_OGG;
	if (flags != Mix_Init(flags)) {
		Err("Unable to initialize mixer: " + string(Mix_GetError()));
	}

	int audio_rate = 22050; Uint16 audio_format = AUDIO_S16SYS; int audio_channels = 2; int audio_buffers = 4096;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		Err("Unable to initialize audio: " + string(Mix_GetError()));
	}


	music = Mix_LoadMUS("bensound-funkyelement.ogg");
	if (music == NULL) {
		Err("Unable to load Music file: " + string(Mix_GetError()));
	}

	jump = Mix_LoadWAV("jump.wav");
	if (jump == NULL) {
		Err("Unable to load WAV file: " + string(Mix_GetError()));
	}
	trap = Mix_LoadWAV("trap.ogg");
	if (trap == NULL) {
		Err("Unable to load WAV file: " + string(Mix_GetError()));
	}
	gameover = Mix_LoadWAV("gameover.ogg");
	if (gameover == NULL) {
		Err("Unable to load WAV file: " + string(Mix_GetError()));
	}
	fish = Mix_LoadWAV("fish.wav");
	if (fish == NULL) {
		Err("Unable to load WAV file: " + string(Mix_GetError()));
	}
	win = Mix_LoadWAV("win.wav");
	if (win == NULL) {
		Err("Unable to load WAV file: " + string(Mix_GetError()));
	}
}

void Audio::BGM()
{
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(music, -1);
		SDL_Delay(150);
	}
	//If music is being played
	else
	{
		//If the music is paused
		if (Mix_PausedMusic() == 1)
		{
			//Resume the music
			Mix_ResumeMusic();
			SDL_Delay(150);
		}
		//If the music is playing
		else
		{
			//Pause the music
			Mix_PauseMusic();
			SDL_Delay(150);
		}
	}
}

void Audio::Jump() {
	if (Mix_Playing(sfx_channel[0]) == 0) {
		sfx_channel[0] = Mix_PlayChannel(-1, jump, 0);
		if (sfx_channel[0] == -1) {
			Err("Unable to play WAV file: " + string(Mix_GetError()));
		}
	}

}
void Audio::Trap() {
	if (Mix_Playing(sfx_channel[1]) == 0) {
		sfx_channel[1] = Mix_PlayChannel(1, trap, 0);
		if (sfx_channel[1] == -1) {
			Err("Unable to play WAV file: " + string(Mix_GetError()));
		}
	}

}
void Audio::GameOver() {
	if (Mix_Playing(sfx_channel[4]) == 0) {
		sfx_channel[4] = Mix_PlayChannel(4, gameover, 0);
		if (sfx_channel[4] == -1) {
			Err("Unable to play WAV file: " + string(Mix_GetError()));
		}
	}

}
void Audio::Fish() {
	if (Mix_Playing(sfx_channel[2]) == 0) {
		sfx_channel[2] = Mix_PlayChannel(2, fish, 0);
		if (sfx_channel[2] == -1) {
			Err("Unable to play WAV file: " + string(Mix_GetError()));
		}
	}

}
void Audio::Win() {
	if (Mix_Playing(sfx_channel[3]) == 0) {
		sfx_channel[3] = Mix_PlayChannel(3, win, 0);
		if (sfx_channel[3] == -1) {
			Err("Unable to play WAV file: " + string(Mix_GetError()));
		}
	}

}
