#pragma once
#ifndef _TEXTRENDERER_H
#define _TEXTRENDERER_H

#include <SDL_ttf.h>
#include <SDL.h>
#include <string.h>
#include <iostream>

using namespace std;

class TextRenderer
{

private:
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	SDL_Surface* text_surface;
	mutable SDL_Rect m_textRect;
	TTF_Font* m_font;

public:
	TextRenderer(SDL_Renderer* renderer);
	~TextRenderer();

	void Render(int xPos, int yPos);
	bool LoadFont(const string& filePath, int fontsize, const string message, SDL_Color color);

};

#endif

