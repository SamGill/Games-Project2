// Programming 2D Games
// Copyright (c) 2012 by: 
// Charles Kelly
// CollisionTypes ship.cpp v1.0

#include "bullet.h"

//=============================================================================
// default constructor
//=============================================================================
Bullet::Bullet() : Entity()
{
    spriteData.width = bulletNS::WIDTH;           // size of Bullet1
    spriteData.height = bulletNS::HEIGHT;
    spriteData.x = bulletNS::X;                   // location on screen
    spriteData.y = bulletNS::Y;
    spriteData.rect.bottom = bulletNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = bulletNS::WIDTH;
	spriteData.scale = 1;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
	
	visible = false;

    currentFrame = 0;
    radius = bulletNS::WIDTH/2.0;                 // collision radius
    collision = false;
    collisionType = entityNS::BOX;
    target = false;
}

//=============================================================================
// Initialize the Bullet.
// Post: returns true if successful, false if failed
//=============================================================================
bool Bullet::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}


//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void Bullet::update(float frameTime)
{

	Entity::update(frameTime);
	   
    spriteData.x += velocity.x * frameTime;
    spriteData.y += velocity.y * frameTime;

	bool isOffscreen = spriteData.x > GAME_WIDTH || spriteData.x < 0 || spriteData.y > GAME_HEIGHT || spriteData.y < 0;

	if (isOffscreen)
	{
		visible = false;
		velocity.x = 0;
		velocity.y = 0;
	}
}