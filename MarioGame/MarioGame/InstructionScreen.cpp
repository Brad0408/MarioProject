#include "InstructionScreen.h"
#include<iostream>


InstructionScreen::InstructionScreen(SDL_Renderer* renderer) :GameScreen(renderer)
{
	SetUpScreen();
}

InstructionScreen::~InstructionScreen()
{
	delete m_background_texture;
	m_background_texture = nullptr;
}

void InstructionScreen::Render()
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void InstructionScreen::Update(float deltaTime, SDL_Event e)
{
}

bool InstructionScreen::SetUpScreen()
{
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/InstructionScreen.png"))
	{
		std::cout << "Failed to Load Backgorund Texture!" << std::endl;
		return false;
	}
}
