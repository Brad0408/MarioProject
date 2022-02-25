#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include <iostream>

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	m_background_texture = nullptr;

	delete mario;
	mario = nullptr;

	delete luigi;
	luigi = nullptr;
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//Update Character
	mario->Update(deltaTime, e);

	luigi->Update(deltaTime, e);
}

void GameScreenLevel1::Render()
{
	//Draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	//Draw Character
	mario->Render();

	luigi->Render();
}

bool GameScreenLevel1::SetUpLevel()
{
	//Load texture
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/test.bmp"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	//Set up the player characters
	mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330));

	luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(70, 330));
}
