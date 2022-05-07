#include "Character.h"

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map)
{
	m_renderer = renderer;
	m_position = start_position;

	//Load texture
	m_texture = new Texture2D(renderer);

	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture!" << std::endl;
	}

	m_facing_direction = FACING_RIGHT;

	m_moving_left = false;
	m_moving_right = false;
	m_movementspeed;

	m_collision_radius = 15.0f;

	m_current_level_map = map;

	m_alive = true;
}

Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render(SDL_Rect camera_rect)
{
	SDL_Rect src_rect = { 0, 0, m_texture->GetWidth(), m_texture->GetHeight() };

	SDL_Rect dest_rect = { m_position.x - camera_rect.x , m_position.y - camera_rect.y, m_texture->GetWidth(), m_texture->GetHeight() };


	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(src_rect, dest_rect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(src_rect, dest_rect, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{

	//Deal with jumping first
	if (m_jumping)
	{
		//Adjust position
		m_position.y -= m_jump_force * deltaTime;

		//Reduce jump force
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		//Is jump force 0?
		if (m_jump_force <= 0.0f)
		{
			m_jumping = false;
		}

	}

	if (m_moving_left)
	{
		MoveLeft(deltaTime, m_movementspeed);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime, m_movementspeed);
	}

	//Collision position variables
	int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;

	//Deal with gravity
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		//Collided with ground so we can jump again
		m_can_jump = true;
	}
}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character::GetPosition()
{
	return m_position;
}

void Character::MoveLeft(float deltaTime, float speed)
{
	m_facing_direction = FACING_LEFT;
	m_position.x -= deltaTime * speed;
}

void Character::MoveRight(float deltaTime, float speed)
{
	m_facing_direction = FACING_RIGHT;
	m_position.x += deltaTime * speed;
}

void Character::AddGravity(float deltaTime)
{
	if (m_position.y + 64 <= SCREEN_HEIGHT)
	{
		m_position.y += GRAVITY * deltaTime;
	}
	else
	{
		m_can_jump = true;
	}
}

void Character::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}

float Character::GetCollisionRadius()
{
	return m_collision_radius;
}

void Character::SetAlive(bool IsAlive)
{
	m_alive = IsAlive;
}
