#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/gtx/intersect.hpp>

#include "Mesh.h"

#include <string>
#include <vector>

struct Font;

extern FT_Library lib;
extern std::vector<Font*> FONT;

// Mesh of all positions of a letter, with ordered pointers to the text objects that use them
struct Letter {
	double
		w = 0, h = 0,
		x_offset = 0,
		y_offset = 0,
		x_buffer = 0;

	Mesh* m = NULL;
};

// A bunch of letters in a row
struct Text {
	void add(char);
	vec3 get_v(unsigned char);
	Font* f = NULL;
	std::vector<std::pair<char, unsigned int>> letters;
	vec3 pos = vec3(0);
	double x=0, y=0, w=0, h=0;
};

// A font with a set of letters
struct Font {
	bool ortho = false;
	unsigned int scale = 0;
	Letter* letters[256] = { };
};

static Letter* create_letter(char c, FT_Face f) {
	Letter* l = new Letter();
	std::vector<Vtx> v;
	std::vector<unsigned int> i;
	l->m = create_mesh(v, i);

	FT_Load_Char(f, c, FT_LOAD_RENDER);

	glGenTextures(1, &l->m->gl_texture);
	glBindTexture(GL_TEXTURE_2D, l->m->gl_texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(
		GL_TEXTURE_2D,
		0, GL_ALPHA,
		f->glyph->bitmap.width,
		f->glyph->bitmap.rows,
		0, GL_ALPHA,
		GL_UNSIGNED_BYTE,
		f->glyph->bitmap.buffer
	);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	l->w = (double)f->glyph->bitmap.width;
	l->h = (double)f->glyph->bitmap.rows;
	l->x_offset = (double)f->glyph->bitmap_left;
	l->y_offset = (double)f->glyph->bitmap_top;
	l->x_buffer = (double)f->glyph->advance.x / 64;

	glBindTexture(GL_TEXTURE_2D, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 0);

	return l;
}

static Font* create_font(
	const char* file_name = "Fonts/Default.ttf",
	unsigned int x_size = 0,
	unsigned int y_size = 640,
	unsigned int scale = 640,
	bool ortho = false) {

	Font* f = new Font();
	FT_Face face = NULL;
	f->ortho = ortho;

	FT_New_Face(lib, file_name, 0, &face);
	FT_Set_Pixel_Sizes(face, x_size, y_size);
	f->scale = scale;

	for (unsigned char c = 0; c < 255; c++)
		f->letters[c] = create_letter(c, face);

	FT_Done_Face(face);

	FONT.push_back(f);

	return f;
};

static Text* create_text(std::string text="Text", Font* f=NULL) {
	Text* t = new Text();

	if (!f) f = create_font();
	t->f = f;
	t->y = f->scale;

	for (char c : text) t->add(c);

	return t;
};

static void translate(Text* t, vec3 v) {
	
}

static void rotate(Text* t, vec3 v) {

}
