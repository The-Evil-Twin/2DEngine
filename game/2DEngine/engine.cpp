#include "engine.h"

//=============================================================================
// Constructor
//=============================================================================
Engine::Engine()
{}

//=============================================================================
// Destructor
//=============================================================================
Engine::~Engine()
{
    releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
// Where we load all of our textures
//=============================================================================
void Engine::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

    // background texture
    if (!backgroundTexture.initialize(graphics,BACKGROUND_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
    if (!characterTexture.initialize(graphics,CHARACTER_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing character texture"));
	if (!groundTexture.initialize(graphics, GROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground texture"));

    // background
    if (!background.initialize(graphics,0,0,0,&backgroundTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));
    // character
    if (!character.initialize(this,playerNS::WIDTH,playerNS::HEIGHT,0,&characterTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing character"));
    // terrain
	if (!ground.initialize(this, terrainNS::WIDTH, terrainNS::HEIGHT, 0, &groundTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ground"));
    character.setX(GAME_WIDTH/4);                           // Character Starting Position
    character.setY(GAME_HEIGHT/4);
	character.setVelocity(VECTOR2(0, -playerNS::SPEED));
    //character.setFrames(CHARACTER_START_FRAME, CHARACTER_END_FRAME);   // animation frames
	// character.setVelocity(VECTOR2());

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Engine::update()
{
    VECTOR2 cv;
	if(input->isKeyDown(CHARACTER_RIGHT_KEY))            // if move right
    {
		character.setVelocity(VECTOR2(100, character.getVelocity().y));
    }
	if (input->isKeyDown(CHARACTER_LEFT_KEY))             // if move left
    {
		character.setVelocity(VECTOR2(-100, character.getVelocity().y));
	}

	if (character.getX() > GAME_WIDTH)               // if off screen right
		character.setX((float)-character.getWidth());     // position off screen left
	if (character.getX() < -character.getWidth())         // if off screen left
		character.setX((float)GAME_WIDTH);           // position off screen right

	// If up key is pressed and the player is not at the bottom of the screen
	if (input->isKeyDown(CHARACTER_UP_KEY) && character.getY() >= GAME_HEIGHT - playerNS::HEIGHT)
    {
		character.jump();
    }
	if (input->isKeyDown(CHARACTER_UP_KEY) && character.collides(ground, cv))
	{
		character.jump();
	}
    if(input->isKeyDown(CHARACTER_DOWN_KEY))             // if move down
    {
		character.setY(character.getY() + frameTime * playerNS::SPEED);
        if (character.getY() > GAME_HEIGHT)              // if off screen bottom
            character.setY((float)-character.getHeight());    // position off screen top
    }

    character.update(frameTime);
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void Engine::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void Engine::collisions()
{
	VECTOR2 cv;
	if (character.collides(ground, cv) && character.getVelocity().y >= 0)
	{
		character.setVelocity(VECTOR2(character.getVelocity().x, 0));
	}
	if (character.collides(ground, cv))
	{
		character.setVelocity(VECTOR2(0, character.getVelocity().y));
	}
		// MessageBox(NULL, "HELLo", "Error", MB_OK);
		// character.setY(10);
		// character.setVelocity(VECTOR2(character.getVelocity().x, 0));
}

//=============================================================================
// Render game items
//=============================================================================
void Engine::render()
{
    graphics->spriteBegin();                // begin drawing sprites

    background.draw();                      
    character.draw();
	ground.draw();

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Engine::releaseAll()
{
    characterTexture.onLostDevice();
	groundTexture.onLostDevice();
    // backgroundTexture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Engine::resetAll()
{
    // backgroundTexture.onResetDevice();
    characterTexture.onResetDevice();
	groundTexture.onResetDevice();

    Game::resetAll();
    return;
}
