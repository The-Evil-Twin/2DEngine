#ifndef _TERRAIN_H
#define _TERRAIN_H

#include "entity.h"
#include "constants.h"

namespace terrainNS
{
	const int WIDTH = 100;
	const int HEIGHT = 20;
	// location on screen
	const int X = GAME_WIDTH / 2;
	const int Y = GAME_HEIGHT;
}

class Terrain : public Entity
{
public:
	Terrain();
};

#endif