#pragma once
#ifndef _MAINMENU_H
#define _MAINMENU_H


#include "GameScreen.h"
#include "Texture2D.h"
#include "Commons.h"

class Texture2D;

class MainMenu : GameScreen
{

private:
	Texture2D* m_background_texture;
	bool SetUpScreen();

public:
	MainMenu(SDL_Renderer* renderer);
	~MainMenu();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

};


#endif
