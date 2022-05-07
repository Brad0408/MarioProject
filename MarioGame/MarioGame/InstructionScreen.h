#pragma once
#ifndef _INSTRUCTIONSCREEN_H
#define _INSTRUCTIONSCREEN_H


#include "GameScreen.h"
#include "Texture2D.h"
#include "Commons.h"

class Texture2D;

class InstructionScreen : GameScreen
{

private:
	Texture2D* m_background_texture;
	bool SetUpScreen();

public:
	InstructionScreen(SDL_Renderer* renderer);
	~InstructionScreen();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

};


#endif
