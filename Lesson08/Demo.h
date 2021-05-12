#ifndef DEMO_H
#define DEMO_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"
#include "Ikan.h"
#include "Player.h"
#include "Ground.h"
#include "Jebakan.h"
#include "Text.h"
#include "Button.h"
#include "Menu.h"
#include "Audio.h"
#include "uid.h"



using namespace glm;

class Demo :
	public Engine::Game
{
public:
	Demo();
	~Demo();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void MenuControl(float deltaTime);
	bool play=false;
private:
	Ikan* ikan[4];
	Player* player;
	Ground* ground[4];
	Jebakan* jebakan[4];
	Menu* menu;
	Text* text;
	Uid* uid;
	void ControlPlayerSprite(float deltaTime);
	int time=60;
	int second = 250;
};
#endif

