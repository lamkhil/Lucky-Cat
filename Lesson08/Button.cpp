#include "Button.h"


Button::Button(float sw, float sh, float xpos, float ypos, string button, string button_hover)
{
	this->xpos = xpos;
	this->ypos = ypos;
	this->sw = sw;
	this->sh = sh;
	this->button = button;
	this->button_hover = button_hover;
	this->program = BuildShader("gui.vert", "gui.frag");

}


Button::~Button()
{

}


void Button::Init()
{
	InitButton(button, button_hover);

}

void Button::Update(float deltaTime)
{

}

void Button::Render()
{

	RenderButton();

}


void Button::InitButton(string buttons, string hover_buttons) {
	UseShader(this->program);
	glGenTextures(1, &texture);
	glGenTextures(1, &hover_texture);
		// Load and create a texture 
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

		// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image(buttons.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

		// Set up vertex data (and buffer(s)) and attribute pointers
	button_width = (float)width;
	button_height = (float)height;

		// Load and create a texture 
	glBindTexture(GL_TEXTURE_2D, hover_texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

		// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	image = SOIL_load_image(hover_buttons.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

		 // Set up vertex data (and buffer(s)) and attribute pointers
	hover_button_width = (float)width;
	hover_button_height = (float)height;
	

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
	projection = ortho(0.0f, static_cast<GLfloat>(sw), static_cast<GLfloat>(sh), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program, "projection"), 1, GL_FALSE, value_ptr(projection));

}

void Button::RenderButton() {
	// Enable transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Activate shader
	UseShader(this->program);
	glUniform1i(glGetUniformLocation(this->program, "text"), 0);

	glBindVertexArray(VAO);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, activeButton ? hover_texture : texture);
	glUniform1i(glGetUniformLocation(this->program, "ourTexture"), 1);

	mat4 model;
	model = translate(model, vec3(xpos, ypos, 0.0f));
	model = scale(model, vec3(button_width, button_height, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program, "model"), 1, GL_FALSE, value_ptr(model));

	glDrawArrays(GL_QUADS, 0, 4);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
}
