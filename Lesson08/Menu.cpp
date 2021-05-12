#include "Menu.h"

Menu::Menu(float screenWidth, float screenHeight)
{
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;
	audio = new Audio();
	audio->InitAudio();
}

Menu::~Menu()
{
	audio->~Audio();
}

void Menu::Init()
{
	judul = new Text(screenWidth, screenHeight);
	judul->Init();
	button[0] = new Button(this->screenWidth, this->screenHeight, (screenWidth-200)/2, ((screenHeight-80)/2)-100, "button_play.png", "button_play_hover.png");
	button[1] = new Button(this->screenWidth, this->screenHeight, (screenWidth - 200) / 2, ((screenHeight - 80) / 2), "button_music.png", "button_music_hover.png");
	button[2] = new Button(this->screenWidth, this->screenHeight, (screenWidth - 200) / 2, ((screenHeight - 80) / 2) + 100, "button_exit.png", "button_exit_hover.png");
	for (size_t i = 0; i < NUM_BUTTON; i++)
	{
		button[i]->Init();
	}
	this->program = BuildShader("gui.vert", "gui.frag");
	buildBGMenu();
}

void Menu::Update(float deltaTime){
}

void Menu::Render()
{	
	renderBGMenu();
	judul->RenderText("LUCKY CAT", (screenWidth-290)/2, 50, 1.5f, vec3(252.0f / 255.0f, 255.0f / 255.0f, 107.0f / 255.0f));
	if (playAudio)
	{
		judul->RenderText("MUSIC : ON", (screenWidth - 196) / 2, 100, 1.0f, vec3(252.0f / 255.0f, 255.0f / 255.0f, 107.0f / 255.0f));
	}
	else {
		judul->RenderText("MUSIC : OFF", (screenWidth - 218) / 2, 100, 1.0f, vec3(252.0f / 255.0f, 255.0f / 255.0f, 107.0f / 255.0f));
	}
	for (size_t i = 0; i < NUM_BUTTON; i++)
	{
		button[i]->Render();
	}
}

void Menu::PlayBGM()
{
	audio->BGM();
	if (playAudio)
	{
		playAudio = false;
	}
	else {
		playAudio = true;
	}
}

void Menu::buildBGMenu() {
	UseShader(this->program);
	glGenTextures(1, &texture);
	// Load and create a texture 
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

		// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("bgMenu.png",&width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.


	GLfloat vertices[] = {
		// Positions	// Texture Coords
		1,  1,			1.0f, 1.0f, // Bottom Right
		1,  0,			1.0f, 0.0f, // Top Right
		0,  0,			0.0f, 0.0f, // Top Left
		0,  1,			0.0f, 1.0f  // Bottom Left 
	};


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(width), static_cast<GLfloat>(height), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program, "projection"), 1, GL_FALSE, value_ptr(projection));

}

void Menu::renderBGMenu() {
	// Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Activate shader
	UseShader(this->program);
	glUniform1i(glGetUniformLocation(this->program, "text"), 0);

	glBindVertexArray(VAO);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(glGetUniformLocation(this->program, "ourTexture"), 1);

	mat4 model;
	model = translate(model, vec3(0, 0, 0.0f));
	model = scale(model, vec3(1280, 720, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program, "model"), 1, GL_FALSE, value_ptr(model));

	glDrawArrays(GL_QUADS, 0, 4);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
}
