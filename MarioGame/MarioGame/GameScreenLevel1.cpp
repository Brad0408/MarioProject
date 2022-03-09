#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Collisions.h"
#include <iostream>

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();

	m_level_map = nullptr;
}

GameScreenLevel1::~GameScreenLevel1()
{
	m_background_texture = nullptr;

	delete mario;
	mario = nullptr;

	delete luigi;
	luigi = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//End shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}

	//Collision Check to console
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
	{
		cout << "Box Hit!" << endl;
	}

	//if (Collisions::Instance()->Circle(mario, luigi))
	//{
	//	cout << "Circle Hit!" << endl;
	//}

	//Update Character
	mario->Update(deltaTime, e);

	luigi->Update(deltaTime, e);

	//Pow Block
	UpdatePowBlock();
}

void GameScreenLevel1::Render()
{
	//Draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);

	//Draw Character
	mario->Render();

	luigi->Render();

	//Pow Block
	m_pow_block->Render();
}

bool GameScreenLevel1::SetUpLevel()
{
	//Load texture
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	SetLevelMap();

	//Set up the player characters
	mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 320), m_level_map);

	luigi = new CharacterLuigi(m_renderer, "Images/LuigiFlip.png", Vector2D(200, 320), m_level_map);

	//Pow Block
	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//Clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//Set the new one
	m_level_map = new LevelMap(map);
}

void GameScreenLevel1::UpdatePowBlock()
{
	//Mario With Pow Block
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), m_pow_block->GetCollisionBox()) && m_pow_block->IsAvaliable())
	{
		cout << "Pow Hit" << endl;
		//Collided with jumping
		if (mario->IsJumping())
		{
			DoScreenShake();
			m_pow_block->TakeHit();
			mario->CancelJump();
		}
	}

	//Luigi With Pow Block
	if (Collisions::Instance()->Box(luigi->GetCollisionBox(), m_pow_block->GetCollisionBox()) && m_pow_block->IsAvaliable())
	{
		cout << "Pow Hit" << endl;
		//Collided with jumping
		if (luigi->IsJumping())
		{
			DoScreenShake();
			m_pow_block->TakeHit();
			luigi->CancelJump();
		}
	}
}

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
}
