#ifndef BUTTON_H
#define BUTTON_H


#include <SOIL/SOIL.h>

#include <SDL/SDL_mixer.h>
#include <SDL/SDL_thread.h>

#include <ft2build.h>
#include <map>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

using namespace glm;

#define NUM_BUTTON 3

class Button :
	public Engine::Game
{
public:
	Button(float sw, float sh, float xpos, float ypos, string button, string button_hover);
	~Button();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	bool activeButton;
	float button_width, button_height, hover_button_width, hover_button_height, ypos = 0, xpos = 0;
private:
	void InitButton(string buttons, string hover_buttons);
	void RenderButton();
	GLuint texture, hover_texture, VBO, VAO, program;
	string button, button_hover;
	float sw, sh;
};
#endif