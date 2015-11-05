#include "player.h"

Player::Player() : Entity()
{
	spriteData.width = playerNS::WIDTH;
	spriteData.height = playerNS::HEIGHT;
	spriteData.x = playerNS::X;
	spriteData.y = playerNS::Y;
	spriteData.rect.bottom = playerNS::HEIGHT;
	spriteData.rect.bottom = playerNS::WIDTH;
	velocity.x = 0;
	velocity.y = playerNS::SPEED;
	frameDelay = 1;
	startFrame = 0;
	endFrame = 0;
	currentFrame = startFrame;
	collisionType = entityNS::BOX;
	mass = playerNS::MASS;
}

void Player::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;

	// If the character hits the ground
	if (spriteData.y > GAME_HEIGHT - playerNS::HEIGHT && velocity.y > 0)
	{
		spriteData.y = GAME_HEIGHT - playerNS::HEIGHT;
		velocity.y = 0;
		velocity.x = 0;
	}

	// printf("%f\n", velocity.y);
	// IF COLLIDES WITH A PIECE OF TERRAIN

	velocity.y += frameTime * GRAVITY;
}