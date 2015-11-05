#ifndef _PLAYER_H
#define _PLAYER_H

#include "entity.h"
#include "constants.h"

namespace playerNS
{
	const int WIDTH = 32;
	const int HEIGHT = 32;
	// location on screen
	const int X = GAME_WIDTH / 2 - WIDTH / 2;
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	// pixels per second
	const float SPEED = 100;
	// minumum Y velocity
	const float MIN_VY = 1;
	const float MASS = 1.0f;
}

class Player : public Entity
{
public:
	Player();
	void update(float frameTime);
};

#endif