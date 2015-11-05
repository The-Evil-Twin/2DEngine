#ifndef _TERRAIN_H
#define _TERRAIN_H

namespace terrainNS
{
	const int WIDTH = 32;
	const int HEIGHT = 32;
	// location on screen
	const int X = GAME_WIDTH / 2 - WIDTH / 2;
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
}

class Terrain
{
public:
	Terrain();
	void update(float frameTime);
};

#endif