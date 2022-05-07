#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Collisions.h"
#include <iostream>

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_level_map = nullptr;

	m_maxTime = 6.0f;
	m_currentTime = 6.0f;

	SetUpLevel();
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

	delete koopa;
	koopa = nullptr;

	delete coin;
	coin = nullptr;

	m_enemies.clear();
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
	//if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
	//{
	//	cout << "Box Hit!" << endl;
	//}

	if (Collisions::Instance()->Circle(mario, luigi))
	{
		cout << "Circle Hit!" << endl;
	}

	//Update Character
	mario->Update(deltaTime, e);

	luigi->Update(deltaTime, e);

	//Pow Block
	UpdatePowBlock();

	//Enemies
	UpdateEnemies(deltaTime, e);

	//Koopa
	m_currentTime = m_currentTime - deltaTime;
	//cout << m_currentTime << endl;

	if (m_currentTime <= 0.0f)
	{
		cout << "Koopa Spawn" << endl;
		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

		m_currentTime = m_maxTime;
	}

	//Coin
	coin->Update(deltaTime, e);
	UpdateCoin();
	//cout << m_score << endl;


	//Screen Scroll
	camera.x = mario->GetPosition().x - SCREEN_WIDTH / 2;

	if (camera.x < 0)
	{
		camera.x = 0;
	}

	if (camera.x > LEVEL_WIDTH - camera.w)
	{
		camera.x = LEVEL_WIDTH - camera.w;
	}


}

void GameScreenLevel1::Render()
{
	//Draw Enemies
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render(camera);
	}

	//Draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), camera, SDL_FLIP_NONE, 0);

	//Draw Character
	mario->Render(camera);

	luigi->Render(camera);

	//Pow Block
	m_pow_block->Render(camera);

	//Coin
	coin->Render(camera);
}

bool GameScreenLevel1::SetUpLevel()
{
	//Load texture
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/newBG.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	SetLevelMap();

	//Set up the player characters
	mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 320), m_level_map);

	luigi = new CharacterLuigi(m_renderer, "Images/LuigiFlip.png", Vector2D(220, 320), m_level_map);

	//Pow Block
	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;


	//Koopa 
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);



	//Coin
	m_score = 0;
	CreateCoin(Vector2D(200, 200));


}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
											{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
											{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
											{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
											{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
											{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
											{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
											{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
											{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
											{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
											{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
											{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
											{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };


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

	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//Check if the enemy is on the bottom of the row tiles
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//Is the enemy off screen to the left / right?
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) || m_enemies[i]->GetPosition().x > LEVEL_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
				{
					m_enemies[i]->SetAlive(false);
				}

			}
			//Now do the update

			m_enemies[i]->Update(deltaTime, e);

			//Check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > LEVEL_WIDTH - 96.0f))
			{
				//ignore collision if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], mario))
				{
					cout << "Enemy hit" << endl;
					if (m_enemies[i]->GetInjured())
					{
						//Enemies dies if they are on their back
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						//Kill Mario
						mario->SetAlive(false);
					}
				}

				if (Collisions::Instance()->Circle(m_enemies[i], luigi))
				{
					cout << "Enemy hit" << endl;
					if (m_enemies[i]->GetInjured())
					{
						//Enemies dies if they are on their back
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						//Kill Luigi
						luigi->SetAlive(false);
					}
				}
			}

			//If the enemy is no longer alive then schedule it for deletion 
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//Remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", position, m_level_map, direction, speed);
	m_enemies.push_back(koopa);
}

void GameScreenLevel1::CreateCoin(Vector2D position)
{
	coin = new CharacterCoin(m_renderer, "Images/Coin.png", position, m_level_map);
}

void GameScreenLevel1::UpdateCoin()
{
	//Mario With Coin
	if (Collisions::Instance()->Circle(mario, coin) && coin->IsAvaliable())
	{
		cout << "Coin Hit" << endl;
		m_score += 10;
		coin->CoinPickup();

	}

	//Luigi With Coin
	if (Collisions::Instance()->Circle(luigi, coin) && coin->IsAvaliable())
	{
		cout << "Coin Hit" << endl;
		m_score += 10;
		coin->CoinPickup();
	}

}