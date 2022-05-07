#include "MainMenu.h"
#include<iostream>


MainMenu::MainMenu(SDL_Renderer* renderer) :GameScreen(renderer)
{
	SetUpScreen();
}

MainMenu::~MainMenu()
{
	delete m_background_texture;
	m_background_texture = nullptr;
}

void MainMenu::Render()
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void MainMenu::Update(float deltaTime, SDL_Event e)
{
}

bool MainMenu::SetUpScreen()
{
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/MainMenu.png"))
	{
		std::cout << "Failed to Load Backgorund Texture!" << std::endl;
		return false;
	}
}
