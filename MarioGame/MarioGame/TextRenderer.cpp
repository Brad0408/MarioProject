#include "TextRenderer.h"

TextRenderer::TextRenderer(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

TextRenderer::~TextRenderer()
{
	m_renderer = nullptr;
}

void TextRenderer::Render(int xPos, int yPos)
{
	m_textRect.x = xPos;
	m_textRect.y = yPos;

	SDL_RenderCopy(m_renderer, m_texture, nullptr, &m_textRect);
}

bool TextRenderer::LoadFont(const string& filePath, int fontsize, const string message, SDL_Color color)
{
	m_font = TTF_OpenFont(filePath.c_str(), fontsize);

	if (!m_font)
	{
		cout << "Failed to load font. Error: " << TTF_GetError() << endl;
	}

	auto text_surface = TTF_RenderText_Solid(m_font, message.c_str(), color);

	if (!text_surface)
	{
		cout << "Failed to load texture surface. Error: " << endl;
	}

	m_texture = SDL_CreateTextureFromSurface(m_renderer, text_surface);

	if (!m_texture)
	{
		cout << "Failed to load texture. Error: " << endl;
	}

	TTF_CloseFont(m_font);
	SDL_FreeSurface(text_surface);

	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_textRect.x, &m_textRect.y);

	return m_texture;
}
