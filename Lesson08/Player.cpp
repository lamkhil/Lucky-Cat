#include "Player.h"

Player::Player(float sw, float sh, float x, float y) {
	this->sw = sw;
	this->sh = sh;
	this->xpos = x;
	this->ypos = y;
	this->xstart = x;
	this->ystart = y;
	sfx = new Audio();
	sfx->InitAudio();
}
Player::~Player()
{
	sfx-> ~Audio();
}
void Player::Init()
{
	BuildPlayerSprite();
	temp_h = frame_height;
	temp_w = frame_width;
}

void Player::Update(float deltaTime)
{
	UpdatePlayerSpriteAnim(deltaTime);
	if (yVelocity<-5.0f)
	{
		sfx->Jump();
	}
	
}

void Player::Render()
{
	DrawPlayerSprite();
}

void Player::UpdatePlayerSpriteAnim(float deltaTime)
{
	// Update animation
	frame_dur += deltaTime;
	UseShader(this->program);
	glUniform1i(glGetUniformLocation(this->program, "maxFrameIndex"), (NUM_FRAMES - 1));

	if (walk_anim && onGround) {
		if (frame_dur > FRAME_DUR)
		{
			frame_dur = 0;
			if (flip==1)
			{
				if (frame_idx == 2) frame_idx = NUM_FRAMES - 1;  else frame_idx--;

				// Pass frameIndex to shader

				glUniform1i(glGetUniformLocation(this->program, "frameIndex"), frame_idx);
			}
			else {
				if (frame_idx == NUM_FRAMES - 1) frame_idx = 2;  else frame_idx++;

				// Pass frameIndex to shader

				glUniform1i(glGetUniformLocation(this->program, "frameIndex"), frame_idx);
			}
		}

	}
	else if (!onGround) {
		glUniform1i(glGetUniformLocation(this->program, "frameIndex"), 1);
	}
	else {
		if (flip==1)
		{
			glUniform1i(glGetUniformLocation(this->program, "frameIndex"), NUM_FRAMES - 1);
		}
		else {
			glUniform1i(glGetUniformLocation(this->program, "frameIndex"), 0);
		}
	}
}

void Player::DrawPlayerSprite() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	UseShader(this->program);
	glUniform1i(glGetUniformLocation(this->program, "ourTexture"), 0);

	// set flip
	glUniform1i(glGetUniformLocation(this->program, "flip"), flip);
	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos, ypos, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width, frame_height, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	glDisable(GL_BLEND);
}

void Player::Start() {
	xpos = xstart;
	ypos = ystart;
	flip = 0;
	lifePoint = 3;
	point = 0;
}

void Player::setGround(Ground *ground, float deltaTime) {
	if (IsCollided(xpos, ypos, frame_width, frame_height, ground->xpos, ground->ypos, ground->frame_width, ground->frame_height)) {

		if (xpos < ground->xpos + ground->frame_width && xpos + frame_width > ground->xpos) {
			ypos = oldypos;
			yVelocity = 0;
			if (ypos < ground->ypos)
			{
				onGround = true;
			}
		}
		if (ypos < ground->ypos + ground->frame_height && ypos + frame_height > ground->ypos) {
			yVelocity += gravity * deltaTime;
			ypos += deltaTime * yVelocity;
			xpos = oldxpos;
		}
	}
}

void Player::setJebakan(Jebakan* jebakan, float deltaTime) {

	if (frame_height==0)
	{
		xpos = xstart;
		ypos = ystart;
		res -= deltaTime;
		if (res < 1)
		{
			frame_height = temp_h;
			frame_width = temp_w;
			res = 500;
		}
	}
	if (xpos < jebakan->xpos + jebakan->frame_width+20 && xpos +20+ frame_width > jebakan->xpos) {
		if (ypos > jebakan->ypos && ypos<jebakan->ypos+sh*0.25)
		{
			jebakan->yVelocity = 3.0f;
		}
	}
	if (IsCollided(xpos, ypos, frame_width, frame_height, jebakan->xpos, jebakan->ypos, jebakan->frame_width, jebakan->frame_height)) {

		lifePoint--;
		if (lifePoint>0)
		{
			sfx->Trap();
		}
		else {
			sfx->GameOver();
		}
		frame_width = 0;
		frame_height = 0;
	}
}

void Player::setIkan(Ikan* ikan, float deltaTime)
{
	if (IsCollided(xpos, ypos, frame_width, frame_height, ikan->xpos, ikan->ypos, ikan->frame_width, ikan->frame_height)) {
		ikan->Destroy();
		point += 10;
		sfx->Fish();
		if (point == 40)
		{
			sfx->Win();
		}
	}
}



void Player::BuildPlayerSprite()
{
	this->program = BuildShader("playerSprite.vert", "playerSprite.frag");

	// Pass n to shader
	UseShader(this->program);
	glUniform1f(glGetUniformLocation(this->program, "n"), 1.0f / NUM_FRAMES);

	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("cat sprite.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width = ((float)width) / NUM_FRAMES / 2;
	frame_height = (float)height / 2;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(sw), static_cast<GLfloat>(sh), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos = frame_width;
	yposGround = sh - (frame_height + 25);
	ypos = (sh - (frame_height + 100));
	gravity = 0.05f;
	xVelocity = 0.8f;

	

}
bool Player::IsCollided(float x1, float y1, float width1, float height1,
	float x2, float y2, float width2, float height2) {
	return (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2);
}