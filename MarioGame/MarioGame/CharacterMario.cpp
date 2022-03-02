#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D start_postion, LevelMap* map) : Character(renderer, imagePath, start_postion, map)
{
	//Load texture
	m_texture = new Texture2D(renderer);

	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture!" << std::endl;
	}

}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{

		case SDLK_RIGHT:
			m_moving_right = true;
			break;

		case SDLK_LEFT:
			m_moving_left = true;
			break;

		case SDLK_UP:
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

		case SDLK_RIGHT:
			m_moving_right = false;
			break;

		case SDLK_LEFT:
			m_moving_left = false;
			break;
		}
		break;

	}
	Character::Update(deltaTime, e);
}
