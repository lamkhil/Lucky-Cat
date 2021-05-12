#ifndef UID_H
#define UID_H

#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"
#include "Player.h"
#include "Text.h"

using namespace glm;

class Uid :
	public Engine::Game
{
public:
	Uid(float sw, float sh, float x, float y, Player *player);
	~Uid();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void Build();
	void Draw();
	float sw = 0, xstart = 0, ystart = 0, sh = 0, xpos = 0, ypos = 0, frame_width = 0, frame_height = 0;
private:
	GLuint VBO, VAO, EBO, texture, program;
	Text* text;
	Player* player;
};
#endif
