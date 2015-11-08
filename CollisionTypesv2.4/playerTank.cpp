// Programming 2D Games
// Copyright (c) 2012 by: 
// Charles Kelly
// CollisionTypes ship.cpp v1.0

#include "playerTank.h"

//=============================================================================
// default constructor
//=============================================================================
PlayerTank::PlayerTank() : Entity()
{
    spriteData.width = playerTankNS::WIDTH;           // size of Ship1
    spriteData.height = playerTankNS::HEIGHT;
    spriteData.x = playerTankNS::X;                   // location on screen
    spriteData.y = playerTankNS::Y;
    spriteData.rect.bottom = playerTankNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = playerTankNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    startFrame = SHIP_START_FRAME;              // first frame of ship animation
    endFrame     = SHIP_END_FRAME;              // last frame of ship animation
    currentFrame = startFrame;
    radius = playerTankNS::WIDTH/2.0;                 // collision radius
    collision = false;
    collisionType = entityNS::CIRCLE;
    target = false;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool PlayerTank::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void PlayerTank::update(float frameTime)
{
    switch (direction)                          // rotate ship
    {
    case playerTankNS::LEFT:
        spriteData.angle -= frameTime * playerTankNS::ROTATION_RATE;  // rotate left
        break;
    case playerTankNS::RIGHT:
        spriteData.angle += frameTime * playerTankNS::ROTATION_RATE;  // rotate right
        break;
    }
    spriteData.x += velocity.x * frameTime;
    velocity.x = 0;
    spriteData.y += velocity.y * frameTime;
    velocity.y = 0;

    Entity::update(frameTime);

    // wrap around screen
    if (spriteData.x > GAME_WIDTH)                  // if off screen right
        spriteData.x = -playerTankNS::WIDTH;              // position off screen left
    else if (spriteData.x < -playerTankNS::WIDTH)         // else if off screen left
        spriteData.x = GAME_WIDTH;                  // position off screen right
    if (spriteData.y < -playerTankNS::HEIGHT)             // if off screen top
        spriteData.y = GAME_HEIGHT;                 // position off screen bottom
    else if (spriteData.y > GAME_HEIGHT)            // else if off screen bottom
        spriteData.y = -playerTankNS::HEIGHT;             // position off screen top
}

