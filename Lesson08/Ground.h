#ifndef GROUND_H
#define GROUND_H

#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

using namespace glm;

class Ground :
	public Engine::Game
{
public:
	Ground(float sw, float sh, float x, float y);
	~Ground();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void BuildGroundSprite();
	void DrawGroundSprite(float x, float y);
	float sw = 0, sh = 0, xpos = 0, ypos = 0, frame_width = 0, frame_height = 0;
private:
	GLuint VBO, VAO, EBO, texture, program;
};
#endif
#pragma once
