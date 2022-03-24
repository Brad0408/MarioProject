#include "CharacterLuigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D start_postion, LevelMap* map) : Character(renderer, imagePath, start_postion, map)
{
	//Load texture
	m_texture = new Texture2D(renderer);

	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture!" << std::endl;
	}

	m_movementspeed = MOVEMENTSPEED;
}


void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{

		case SDLK_d:
			m_moving_right = true;
			break;

		case SDLK_a:
			m_moving_left = true;
			break;

		case SDLK_SPACE:
			if (m_can_jump)
			{
				Jump();
			}
			break;
		}
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{

		case SDLK_d:
			m_moving_right = false;
			break;

		case SDLK_a:
			m_moving_left = false;
			break;
		}
		break;
	}
	Character::Update(deltaTime, e);
}
