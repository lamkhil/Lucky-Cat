#ifndef AUDIO_H
#define AUDIO_H


#include <SOIL/SOIL.h>

#include <SDL/SDL_mixer.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

using namespace glm;

class Audio :
	public Engine::Game
{
public:
	Audio();
	~Audio();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void InitAudio();
	void BGM();
	void Jump();
	void Trap();
	void GameOver();
	void Fish();
	void Win();
	float frame_width = 0, frame_height = 0;
private:
	Mix_Chunk* jump = NULL;
	Mix_Chunk* trap = NULL;
	Mix_Chunk* gameover = NULL;
	Mix_Chunk* fish = NULL;
	Mix_Chunk* win = NULL;
	Mix_Music* music = NULL;
	int sfx_channel[5] = {-1,1,2,3,4};
};
#endif

