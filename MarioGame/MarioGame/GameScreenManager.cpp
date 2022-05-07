#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "MainMenu.h"
#include "InstructionScreen.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;
	m_current_screen = nullptr;

	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	m_renderer = nullptr;

	delete m_current_screen;
	m_current_screen = nullptr;
}

void GameScreenManager::Render()
{
	m_current_screen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	m_current_screen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	//Clear up the old screen
	if (m_current_screen != nullptr)
	{
		delete m_current_screen;
	}

	GameScreenLevel1* tempScreen;
	GameScreenLevel2* tempScreen2;
	MainMenu* tempScreenMenu;
	InstructionScreen* tempScreenInstruction;

	switch (new_screen)
	{
	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*)tempScreen;
		tempScreen = nullptr;
		break;

	case SCREEN_LEVEL2:
		tempScreen2 = new GameScreenLevel2(m_renderer);
		m_current_screen = (GameScreen*)tempScreen2;
		tempScreen2 = nullptr;
		break;

	case SCREEN_MENU:
		tempScreenMenu = new MainMenu(m_renderer);
		m_current_screen = (GameScreen*)tempScreenMenu;
		tempScreenMenu = nullptr;
		break;

	case SCREEN_INSTRUCTIONS:
		tempScreenInstruction = new InstructionScreen(m_renderer);
		m_current_screen = (GameScreen*)tempScreenInstruction;
		tempScreenInstruction = nullptr;
		break;

	default:
		break;
	}
}


