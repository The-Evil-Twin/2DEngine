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
//=============================================================================
void Engine::initialize(HWND hwnd)
{
    Game::initialize(hwnd); // throws GameError

    // background texture
    //if (!backgroundTexture.initialize(graphics,BACKGROUND_IMAGE))
    //    throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background texture"));
    // spacecharacter texture
    if (!characterTexture.initialize(graphics,CHARACTER_IMAGE))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing character texture"));

    // background
    //if (!background.initialize(graphics,0,0,0,&backgroundTexture))
    //    throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing background"));

    // character
    if (!character.initialize(graphics,0,0,0,&characterTexture))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing character"));
    character.setX(GAME_WIDTH/4);                           // Character Starting Position
    character.setY(GAME_HEIGHT/4);
    //character.setFrames(CHARACTER_START_FRAME, CHARACTER_END_FRAME);   // animation frames
    character.setCurrentFrame(CHARACTER_START_FRAME);     // starting frame
    character.setFrameDelay(CHARACTER_ANIMATION_DELAY);

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void Engine::update()
{
    if(input->isKeyDown(CHARACTER_RIGHT_KEY))            // if move right
    {
        character.setX(character.getX() + frameTime * CHARACTER_SPEED);
        if (character.getX() > GAME_WIDTH)               // if off screen right
            character.setX((float)-character.getWidth());     // position off screen left
    }
    if(input->isKeyDown(CHARACTER_LEFT_KEY))             // if move left
    {
        character.setX(character.getX() - frameTime * CHARACTER_SPEED);
        if (character.getX() < -character.getWidth())         // if off screen left
            character.setX((float)GAME_WIDTH);           // position off screen right
    }
    if(input->isKeyDown(CHARACTER_UP_KEY))               // if move up
    {
        character.setY(character.getY() - frameTime * CHARACTER_SPEED);
        if (character.getY() < -character.getHeight())        // if off screen top
            character.setY((float)GAME_HEIGHT);          // position off screen bottom
    }
    if(input->isKeyDown(CHARACTER_DOWN_KEY))             // if move down
    {
        character.setY(character.getY() + frameTime * CHARACTER_SPEED);
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
{}

//=============================================================================
// Render game items
//=============================================================================
void Engine::render()
{
    graphics->spriteBegin();                // begin drawing sprites

    background.draw();                          // add the orion nebula to the scene
    character.draw();                            // add the spacecharacter to the scene

    graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void Engine::releaseAll()
{
    characterTexture.onLostDevice();
    backgroundTexture.onLostDevice();

    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void Engine::resetAll()
{
    backgroundTexture.onResetDevice();
    characterTexture.onResetDevice();

    Game::resetAll();
    return;
}
