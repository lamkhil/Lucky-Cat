#ifndef TEXT_H
#define TEXT_H


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

using namespace glm;

#define FONTSIZE 40
#define FONTNAME "BalooThambi2-Bold.ttf"

struct Character {
	GLuint TextureID; // ID handle of the glyph texture
	ivec2 Size; // Size of glyph
	ivec2 Bearing; // Offset from baseline to left/top of glyph
	GLuint Advance; // Offset to advance to next glyph
};

class Text :
	public Engine::Game
{
public:
	Text(float sw, float sh);
	~Text();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void RenderText(string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color);
private:
	void InitText();
	float sw, sh;
	map<GLchar, Character> Characters;
	GLuint VBO, VBO2, VAO, VAO2, program;
};
#endif

