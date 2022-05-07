#pragma once
#ifndef _CHARACTERCOIN_H
#define _CHARACTERCOIN_H

#include <SDL.h>
#include "Character.h"

class CharacterCoin : public Character
{

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_frame_delay;
	float m_current_frame;

	float m_hit = 1.0f;

public:
	CharacterCoin(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map);
	virtual void Render() override;
	virtual void Update(float deltaTime, SDL_Event e) override;

	void CoinPickup();
	bool IsAvaliable() { return m_hit > 0; }

};


#endif
