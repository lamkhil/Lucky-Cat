#ifndef MENU_H
#define MENU_H


#include <SOIL/SOIL.h>

#include <SDL/SDL_mixer.h>
#include <SDL/SDL_thread.h>

#include <ft2build.h>
#include <freetype/freetype.h>
#include <map>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"
#include "Button.h"
#include "Text.h"
#include "Audio.h"

using namespace glm;

#define NUM_BUTTON 3

class Menu :
	public Engine::Game
{
public:
	Menu(float screenHeight, float screenWidth);
	~Menu();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void PlayBGM();
	void buildBGMenu();
	void renderBGMenu();
	Button* button[NUM_BUTTON];
	int activeButtonIndex = -2;
private:
	Text* judul;
	Audio* audio;
	bool playAudio = false;
	float screenWidth = 0, screenHeight = 0;
	GLuint texture, VBO, VAO, program;
};
#endif