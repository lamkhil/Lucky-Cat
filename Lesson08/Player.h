#ifndef PLAYER_H
#define PLAYER_H

#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"
#include "Ground.h"
#include "Jebakan.h"
#include "Ikan.h"
#include "Audio.h"
#define NUM_FRAMES 9
#define FRAME_DUR 60
using namespace glm;

class Player :
	public Engine::Game
{
public:
	Player(float sw, float sh, float x, float y);
	~Player();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void BuildPlayerSprite();
	bool IsCollided(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);
	void DrawPlayerSprite();
	void Start();
	void setGround(Ground *ground, float deltaTime);
	void setJebakan(Jebakan* jebakan, float deltaTime);
	void setIkan(Ikan* ikan, float deltaTime);
	void UpdatePlayerSpriteAnim(float deltaTime);
	float sw = 0, point=0, lifePoint = 3, sh = 0, xstart = 0, ystart = 0, xpos = 0, ypos = 0, frame_width = 0, frame_height = 0, frame_dur = 0, oldxpos = 0, oldypos = 0, gravity = 0, xVelocity = 0, yVelocity = 0, yposGround = 0, onTop = 0, temp_w = 0, temp_h=0;
	bool walk_anim = false, onGround = true;
	unsigned int frame_idx = 0, flip = 0;
private:
	GLuint VBO, VAO, EBO, texture, program;
	Audio* sfx;
	int res = 2*250;
};
#endif
