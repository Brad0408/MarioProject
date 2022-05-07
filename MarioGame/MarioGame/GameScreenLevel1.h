#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H


#include "GameScreen.h"
#include "Commons.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"
#include "Collisions.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include <vector>


class Texture2D;

class Character;

class PowBlock;

class GameScreenLevel1 : GameScreen
{

private:
	Texture2D* m_background_texture;
	CharacterMario* mario;
	CharacterLuigi* luigi;
	CharacterKoopa* koopa;
	CharacterCoin* coin;
	bool SetUpLevel();

	void SetLevelMap();
	LevelMap* m_level_map;

	PowBlock* m_pow_block;
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	void DoScreenShake();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	vector<CharacterKoopa*> m_enemies;

	float m_maxTime;
	float m_currentTime;

	void CreateCoin(Vector2D position);
	int m_score;


	float x;
	float y;

	SDL_Rect camera = { static_cast<int>(x), static_cast<int>(y), SCREEN_WIDTH, SCREEN_HEIGHT };

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void UpdatePowBlock();
	void UpdateCoin();

};

#endif

