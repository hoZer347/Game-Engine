#pragma once

#include "Mesh.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <fstream>
#include <string>
#include <vector>
#include <map>

struct Letter {
	Mesh* m = NULL;
	vec2 s = vec2(0);
	float offset = 0;
	auto& operator[](unsigned int i) { return m->vtxs[i]; };
};

struct Font {
	FT_Face f = NULL;
	std::vector<Letter> l;
};

struct Text {
	Font* f = NULL;
	std::string s;
	std::map<Mesh*, std::vector<unsigned int>> l;
};

extern FT_Library lib;
extern std::vector<Font*> FONT;
extern std::vector<Text*> TEXT;

// Creates a glyph texture and a freetype face for a given font
static Font* create_font(const char* file_name = "Fonts/Default.ttf", int size = 640) {
	Font* font = new Font();

	FT_New_Face(lib, file_name, NULL, &font->f);
	FT_Set_Pixel_Sizes(font->f, size, 0);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (int i = 0; i < 128; i++) {
		Mesh* m = create_square();
		m->vtxs.clear();
		m->inds.clear();

		FT_Load_Glyph(font->f, FT_Get_Char_Index(font->f, (char)i), FT_LOAD_DEFAULT);
		FT_Render_Glyph(font->f->glyph, FT_RENDER_MODE_NORMAL);

		glGenTextures(1, &m->gl_texture);
		glBindTexture(GL_TEXTURE_2D, m->gl_texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_ALPHA,
			font->f->glyph->bitmap.width,
			font->f->glyph->bitmap.rows,
			0,
			GL_ALPHA,
			GL_UNSIGNED_BYTE,
			font->f->glyph->bitmap.buffer
		);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		Letter l = {
			m,
			vec2((float)font->f->glyph->bitmap.width / size, (float)font->f->glyph->bitmap.rows / size),
			(float)font->f->glyph->advance.x / (64 * size)
		};

		font->l.push_back(l);

		FONT.push_back(font);
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 0);

	return font;
}

// Generates text using a font
static Text* create_text(std::string text, Font* font) {
	Text* t = new Text();
	t->f = font;
	float x=0, y=0;

	for (auto& c : text) {
		if (c == '\n') {
			y -= (float) font->f->height / (4 * 640);
			x = 0;
			continue;
		}

		Letter l = font->l[c];

		unsigned int i = l.m->vtxs.size();

		// Loading vertices
		l.m->vtxs.push_back(Vtx());
		l.m->vtxs.push_back(Vtx());
		l.m->vtxs.push_back(Vtx());
		l.m->vtxs.push_back(Vtx());
		l.m->inds.push_back(i + 0);
		l.m->inds.push_back(i + 1);
		l.m->inds.push_back(i + 2);
		l.m->inds.push_back(i + 3);
		
		// Setting Positions
		l.m->vtxs[i + BOTTOM_LEFT].pos		= vec3(x, y, 0);
		l.m->vtxs[i + BOTTOM_RIGHT].pos		= vec3(l.s.x + x, y, 0);
		l.m->vtxs[i + TOP_RIGHT].pos		= vec3(l.s.x + x, l.s.y + y, 0);
		l.m->vtxs[i + TOP_LEFT].pos			= vec3(x, l.s.y + y, 0);

		// Setting tex coords
		l.m->vtxs[i + BOTTOM_LEFT].cds		= vec2(0, 1);
		l.m->vtxs[i + BOTTOM_RIGHT].cds		= vec2(1, 1);
		l.m->vtxs[i + TOP_RIGHT].cds		= vec2(1, 0);
		l.m->vtxs[i + TOP_LEFT].cds			= vec2(0, 0);

		x += l.offset;

		t->l[l.m].push_back(i + 0);
		t->l[l.m].push_back(i + 1);
		t->l[l.m].push_back(i + 2);
		t->l[l.m].push_back(i + 3);

		t->s += c;
	}

	TEXT.push_back(t);

	return t;
}

// Unloads all text faces
static void unload_faces() {
	for (auto& f : FONT)
		FT_Done_Face(f->f);
}

