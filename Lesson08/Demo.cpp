#include "Demo.h"


Demo::Demo()
{
	
}


Demo::~Demo()
{
	menu-> ~Menu();
	player-> ~Player();
}

void Demo::Init()
{
	menu = new Menu(GetScreenWidth(), GetScreenHeight());
	text = new Text(GetScreenWidth(), GetScreenHeight());
	text->Init();
	ikan[0] = new Ikan(GetScreenWidth(), GetScreenHeight(), 700, GetScreenHeight() * 0.9);
	ikan[1] = new Ikan(GetScreenWidth(), GetScreenHeight(), 400, GetScreenHeight() * 0.3);
	ikan[2] = new Ikan(GetScreenWidth(), GetScreenHeight(), 700, GetScreenHeight() * 0.6);
	ikan[3] = new Ikan(GetScreenWidth(), GetScreenHeight(), 100, GetScreenHeight() * 0.15);
	player = new Player(GetScreenWidth(), GetScreenHeight(), 200, 600);
	ground[0] = new Ground(GetScreenWidth(), GetScreenHeight(), (GetScreenWidth() - GetScreenWidth()), (GetScreenHeight() - 25));
	ground[1] = new Ground(GetScreenWidth(), GetScreenHeight(), (GetScreenWidth() * 0.8 - GetScreenWidth()), (GetScreenHeight() * 0.75 - 25));
	ground[2] = new Ground(GetScreenWidth(), GetScreenHeight(), (GetScreenWidth() * 1.2 - GetScreenWidth()), (GetScreenHeight() * 0.5 - 25));
	ground[3] = new Ground(GetScreenWidth(), GetScreenHeight(), (GetScreenWidth() * 0.8 - GetScreenWidth()), (GetScreenHeight() * 0.25 - 25));
	jebakan[0] = new Jebakan(GetScreenWidth(), GetScreenHeight(), (GetScreenWidth() / 2), (GetScreenHeight() * 0.75));
	jebakan[1] = new Jebakan(GetScreenWidth(), GetScreenHeight(), (GetScreenWidth() * 0.7), (GetScreenHeight() * 0.5));
	jebakan[2] = new Jebakan(GetScreenWidth(), GetScreenHeight(), (GetScreenWidth() * 0.25), (GetScreenHeight() * 0.25));
	jebakan[3] = new Jebakan(GetScreenWidth(), GetScreenHeight(), (GetScreenWidth() * 0.7), (GetScreenHeight() * 0.25));
	uid = new Uid(GetScreenWidth(), GetScreenHeight(), 10, 10, player);
	for (size_t i = 0; i < 4; i++)
	{
		ground[i]->Init();
		ikan[i]->Init();
		jebakan[i]->Init();
	}
	player ->Init();
	menu->Init();
	uid -> Init();

	//control Mapppp
	InputMapping("Move Right", SDLK_RIGHT);
	InputMapping("Move Left", SDLK_LEFT);
	InputMapping("Move Right", SDLK_d);
	InputMapping("Move Left", SDLK_a);
	InputMapping("Move Right", SDL_BUTTON_RIGHT);
	InputMapping("Move Left", SDL_BUTTON_LEFT);
	InputMapping("Move Right", SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	InputMapping("Move Left", SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	InputMapping("Move Up", SDLK_UP);
	InputMapping("Quit", SDLK_ESCAPE);
	InputMapping("SelectButton", SDLK_SPACE);
	InputMapping("Move Down", SDLK_DOWN);
}

void Demo::Update(float deltaTime)
{
	
	
	if (IsKeyDown("Quit")) {
		
	}
	player->Update(deltaTime);
	if (play)
	{

		ControlPlayerSprite(deltaTime);
	}
	else {

		MenuControl(deltaTime);
	}

	if (play&&time>-1)
	{
		if (second > 0)
		{
			second -= deltaTime;
		}
		else
		{

			time -= 1;
			second = 250;
		}
	}

}


void Demo::Render()
{

	//Setting Viewport
	glViewport(0, 0, GetScreenWidth(), GetScreenHeight());
	if (play)
	{

		//Clear the color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Set the background color
		glClearColor(0.19f, 0.88f, 0.85f, 0.0f);

		player->Render();
		uid-> Render();
		for (size_t i = 0; i < 4; i++)
		{
			ground[i]->Render();
			jebakan[i]->Render();
			ikan[i]->Render();
		}

		text->RenderText("Time Remaining : "+ to_string(time) +" s", GetScreenWidth()-193, 10, 0.5f, vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
		if (player->lifePoint==0 || time < 0) {
			//Clear the color and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//Set the background color
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			text->RenderText("Game Over", (GetScreenWidth() - 199)/2, (GetScreenHeight() - 61)/2 -50, 1.0f, vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
			text->RenderText("Press ESC to Main Menu", (GetScreenWidth() - 423) / 2, (GetScreenHeight() - 61) / 2 + 50, 1.0f, vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
		}
		if (player->point==40)
		{
			//Clear the color and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//Set the background color
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			text->RenderText("You Win", (GetScreenWidth() - 144) / 2, (GetScreenHeight() - 61) / 2 - 50, 1.0f, vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
			text->RenderText("Press ESC to Main Menu", (GetScreenWidth() - 423) / 2, (GetScreenHeight() - 61) / 2 + 50, 1.0f, vec3(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f));
			
		}
	}
	else {

		//Clear the color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Set the background color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		menu->Render();

		player->Start();
		for (size_t i = 0; i < 4; i++)
		{
			ikan[i]->Start();
			jebakan[i]->Start();
		}
		time = 40;
	}
}

void Demo::MenuControl(float deltaTime) {
	for (size_t i = 0; i < NUM_BUTTON; i++)
	{
		if (i != menu->activeButtonIndex)
		{
			menu->button[i]->activeButton = false;
		}
		else
		{
			menu->button[i]->activeButton = true;
		}
	}
	if (IsKeyDown("SelectButton")) {
		if (menu->activeButtonIndex==0)
		{
			play = true;
		}
		else if (menu->activeButtonIndex == 2) {
			SDL_Quit();
			exit(0);
		}
		else if (menu->activeButtonIndex == 1) {
			menu->PlayBGM();
		}
	}

	if (IsKeyUp("Move Down")) {
		if (menu->activeButtonIndex < NUM_BUTTON - 1) {
			menu->activeButtonIndex++;
			SDL_Delay(150);
		}
	}

	if (IsKeyUp("Move Up")) {
		if (menu->activeButtonIndex > 0) {
			menu->activeButtonIndex--;
			SDL_Delay(150);
		}
	}
}

void Demo::ControlPlayerSprite(float deltaTime)
{
	player->walk_anim = false;
	player->oldxpos = player->xpos;
	player->oldypos = player->ypos;

	if (IsKeyDown("Quit"))
	{
		play = false;
	}

	if (IsKeyDown("Move Right")) {
		player->xpos += deltaTime * player->xVelocity;
		player->flip = 0;
		player->walk_anim = true;
	}

	if (IsKeyDown("Move Left")) {
		player->xpos -= deltaTime * player->xVelocity;
		player->flip = 1;
		player->walk_anim = true;
	}
	if (IsKeyDown("Move Up")) {
		if (player->onGround) {
			player->yVelocity = -6.0f;
			player->onGround = false;
		}
	}
	if (IsKeyUp("Move Up")) {
		if (player->yVelocity < -6.0f) {
			player->yVelocity = -3.0f;
		}
	}
	player->yVelocity += player->gravity * deltaTime;
	player->ypos += deltaTime * player->yVelocity;

	if (player->ypos > player->yposGround) {
		player->ypos = player->yposGround;
		player->yVelocity = 0;
		player->onGround = true;
	}
	if (player->xpos < 0) {
		player->xpos = 0;
	}
	if (player->xpos > (GetScreenWidth() - player->frame_width)) {
		player->xpos = GetScreenWidth()- player->frame_width;
	}

	// check collision between bart and crate
	for (size_t i = 0; i < 4; i++)
	{
		player->setGround(ground[i], deltaTime);
		player->setJebakan(jebakan[i], deltaTime);
		jebakan[i]->ypos += jebakan[i]->yVelocity * deltaTime;
		player->setIkan(ikan[i], deltaTime);
	}
}



int main(int argc, char** argv) {

	Engine::Game& game = Demo();
	game.Start("Lucky Cat", 1280, 720, false, WindowFlag::WINDOWED, 60, 0.25);

	return 0;
}
