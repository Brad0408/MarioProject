#pragma once
#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H

#include <SDL.h>
#include "Character.h"

class CharacterKoopa : public Character
{

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;
	FACING m_facing_direction;

	void FlipRightwayUp();

public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed);
	virtual void Render() override;
	virtual void Update(float deltaTime, SDL_Event e) override;

	void TakeDamage();
	void Jump();

	bool GetInjured();

};

#endif