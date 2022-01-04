#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/gtx/intersect.hpp>

#include "Window.hpp"
#include "Mesh.h"

#include <string>
#include <vector>
#include <map>

class Letter;
class Text;
class Font;

extern FT_Library lib;
extern std::vector<Text*> TEXT;
extern std::vector<unsigned int> _TEXT;
extern std::vector<Font*> FONT;
extern std::vector<unsigned int> _FONT;
extern std::vector<unsigned int> FTXS;

// Represents location of letter in a font
class Letter {
public:
	vec2
		a = vec2(), // Advance
		b = vec2(), // Bearing
		s = vec2(); // Size

	unsigned int
		x = 0; // Position on texture
};

// Displays text
class Text {
public:
	void add(unsigned char, Font*);
	vec3 pos(unsigned char);

	Mesh* m = blank_mesh();

	vec3
		loc = vec3(0),
		stride = vec3(0);

	unsigned int
		index = 0;

	double
		h=0;
};

// Font for displaying text
class Font {
public:
	~Font() {
		delete m;

		for (auto& l : letters)
			delete l;
	}

	Letter* letters[256] = { };

	vec2 s = vec2();

	unsigned int
		scale=0,
		index=0;

	Mesh* m = NULL;
};

// Creates an empty mesh and letters to be copied into text objects
static Font* create_font(
	const char* file_name = "Fonts/Default.ttf",
	unsigned int x_size = 0,
	unsigned int y_size = 640,
	unsigned int scale = 1024) {
	Font* f = new Font();
	f->m = blank_mesh(false);
	f->scale = scale;

	FT_Face face;
	FT_New_Face(lib, file_name, 0, &face);
	FT_Set_Char_Size(face, x_size, y_size, 0, scale);

	glGenTextures(1, &f->m->gl_texture);
	glBindTexture(GL_TEXTURE_2D, f->m->gl_texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	unsigned int w=0, h=0;

	// Creating blank texture of desired dimensions
	for (unsigned char c = 0; c < 255; c++) {
		FT_Load_Char(face, c, FT_LOAD_RENDER);

		w +=          face->glyph->bitmap.width + 1;
		h  = std::max(face->glyph->bitmap.rows, h);
	}

	glTexImage2D(
		GL_TEXTURE_2D,
		0, GL_ALPHA,
		w, h+10,
		0, GL_ALPHA,
		GL_UNSIGNED_BYTE, 0);
	
	f->s = vec2(w, h);
	//

	// Allocating blank texture
	unsigned int x = 0;

	for (unsigned char c = 0; c < 255; c++) {
		FT_Load_Char(face, c, FT_LOAD_RENDER);

		glTexSubImage2D(
			GL_TEXTURE_2D,
			NULL, x, NULL,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer);

		f->letters[c] = new Letter();
		Letter* l = f->letters[c];
		
		l->a = vec2(face->glyph->advance.x,          face->glyph->advance.y);
		l->b = vec2(face->glyph->bitmap_left,        face->glyph->bitmap_top);
		l->s = vec2(face->glyph->bitmap.width, -(int)face->glyph->bitmap.rows);
		l->x = x;

		x += face->glyph->bitmap.width + 1;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 0);
	
	FT_Done_Face(face);
	//
	
	if (!_FONT.empty()) {
		FONT[_FONT.back()] = f;
		f->index = _FONT.back();
		_FONT.pop_back();
	} else {
		f->index = FONT.size();
		FONT.push_back(f);
	}

	FTXS.push_back(f->m->gl_texture);

	return f;
}

// Safely deletes a font
static void delete_font(Font* f) {
	if (!f) return;

	_FONT.push_back(f->index);

	FONT[f->index] = NULL;

	for (auto& l : f->letters)
		delete l;

	delete f->m;
	delete f;
}

// Creates a letter mesh by copying the font's empty one
static Text* create_text(std::string text, Font* f, bool add=true) {
	Text* t = new Text();

	t->m->gl_texture = f->m->gl_texture;
	t->m->show = true;

	if (add) {
		if (!_TEXT.empty()) {
			TEXT[_TEXT.back()] = t;
			t->index = _TEXT.back();
			_TEXT.pop_back();
		}
		else {
			t->index = TEXT.size();
			TEXT.push_back(t);
		}
	}

	for (unsigned char c : text)
		t->add(c, f);

	return t;
}

// Safely deletes a text object (NOTE: Does not deallocate mesh!)
static void delete_text(Text* t) {
	if (!t) return;

	_TEXT.push_back(t->index);

	TEXT[t->index] = NULL;

	delete_mesh(t->m);

	delete t;
}

// Deallocates all text textures
static void close_text() {
	for (auto& t : TEXT)
		if (t)
			delete t;

	for (auto& f : FONT)
		if (f)
			delete f;

	if (!FTXS.empty())
		glDeleteTextures(FTXS.size(), &FTXS[0]);
}
