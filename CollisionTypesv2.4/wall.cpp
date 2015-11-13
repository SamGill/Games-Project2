// Programming 2D Games
// Copyright (c) 2012 by: 
// Charles Kelly
// CollisionTypes ship.cpp v1.0

#include "wall.h"

//=============================================================================
// default constructor
//=============================================================================
Wall::Wall() : Entity()
{
	spriteData.width = wallNS::WIDTH;           // size of Wall1
	spriteData.height = wallNS::HEIGHT;
	spriteData.x = wallNS::X;                   // location on screen
	spriteData.y = wallNS::Y;
	spriteData.rect.bottom = wallNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = wallNS::WIDTH;
	spriteData.scale = 1;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y

	
	currentFrame = 0;
	collision = false;
	collisionType = entityNS::BOX;
}

//=============================================================================
// Initialize the Wall.
// Post: returns true if successful, false if failed
//=============================================================================
bool Wall::initialize(Game *gamePtr, int width, int height, int ncols,
						  TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}


//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
