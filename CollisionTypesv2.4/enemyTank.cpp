#include "enemyTank.h"

//=============================================================================
// default constructor
//=============================================================================
enemyTank::enemyTank() : Entity()
{
    spriteData.width = enemyTankNS::WIDTH;           // size of Ship1
    spriteData.height = enemyTankNS::HEIGHT;
    spriteData.x = enemyTankNS::X;                   // location on screen
    spriteData.y = enemyTankNS::Y;
    spriteData.rect.bottom = enemyTankNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = enemyTankNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    startFrame = SHIP_START_FRAME;              // first frame of ship animation
    endFrame     = SHIP_END_FRAME;              // last frame of ship animation
    currentFrame = startFrame;
    radius = enemyTankNS::WIDTH/2.0;                 // collision radius
    collision = false;
    collisionType = entityNS::CIRCLE;
    target = false;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================
bool enemyTank::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void enemyTank::update(float frameTime)
{
    switch (direction)                          // rotate ship
    {
    case enemyTankNS::LEFT:
        spriteData.angle -= frameTime * enemyTankNS::ROTATION_RATE;  // rotate left
        break;
    case enemyTankNS::RIGHT:
        spriteData.angle += frameTime * enemyTankNS::ROTATION_RATE;  // rotate right
        break;
    }
    spriteData.x += velocity.x * frameTime;
    velocity.x = 0;
    spriteData.y += velocity.y * frameTime;
    velocity.y = 0;

    Entity::update(frameTime);

    // wrap around screen
    if (spriteData.x > GAME_WIDTH)                  // if off screen right
        spriteData.x = -enemyTankNS::WIDTH;              // position off screen left
    else if (spriteData.x < -enemyTankNS::WIDTH)         // else if off screen left
        spriteData.x = GAME_WIDTH;                  // position off screen right
    if (spriteData.y < -enemyTankNS::HEIGHT)             // if off screen top
        spriteData.y = GAME_HEIGHT;                 // position off screen bottom
    else if (spriteData.y > GAME_HEIGHT)            // else if off screen bottom
        spriteData.y = -enemyTankNS::HEIGHT;             // position off screen top
}

