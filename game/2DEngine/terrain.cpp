#include "terrain.h"

Terrain::Terrain()
{
	spriteData.width = terrainNS::WIDTH;
	spriteData.height = terrainNS::HEIGHT;
	spriteData.x = terrainNS::X;
	spriteData.y = terrainNS::Y;
	spriteData.rect.bottom = terrainNS::HEIGHT;
	spriteData.rect.bottom = terrainNS::WIDTH;
	velocity.x = 0;
	velocity.y = 0;
	frameDelay = 1;
	startFrame = 0;
	endFrame = 0;
	currentFrame = startFrame;
	collisionType = entityNS::BOX;
}