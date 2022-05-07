#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map) : Character(renderer, imagePath, start_position, map)
{
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
}

void CharacterCoin::Render()
{
	if (m_hit > 0)
	{
		//Get the portion of the sprite sheet you want to draw {xPos, yPos, width of sprite, height of sprite}
		SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame, 0, m_single_sprite_w, m_single_sprite_h };

		//Deterime where you want it drawn
		SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);

	}
}


void CharacterCoin::Update(float deltaTime, SDL_Event e)
{
	m_frame_delay -= deltaTime;

	if (m_frame_delay <= 0.0f)
	{
		//Reset frame delay count 
		m_frame_delay = ANIMATION_DELAY;

		//Move the frame over
		m_current_frame++;

		//Loop frame around if it goes beyond the number of frame
		if (m_current_frame > 2)
		{
			m_current_frame = 0;
		}
	}
}

void CharacterCoin::CoinPickup()
{
	m_hit -= 1;
}

