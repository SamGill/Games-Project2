// Programming 2D Games
// Copyright (c) 2012 by: 
// Charles Kelly
// CollisionTypes ship.cpp v1.0

#include "tankHead.h"

//=============================================================================
// default constructor
//=============================================================================
TankHead::TankHead() : Entity()
{
    spriteData.width = tankHeadNS::WIDTH;           // size of TankHead1
    spriteData.height = tankHeadNS::HEIGHT;
    spriteData.x = tankHeadNS::X;                   // location on screen
    spriteData.y = tankHeadNS::Y;
    spriteData.rect.bottom = tankHeadNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = tankHeadNS::WIDTH;
	spriteData.scale = 1;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
    //startFrame = SHIP_START_FRAME;              // first frame of ship animation
    //endFrame     = SHIP_END_FRAME;              // last frame of ship animation
    currentFrame = 0;
    radius = tankHeadNS::WIDTH/2.0;                 // collision radius
    collision = false;
    collisionType = entityNS::BOX;
    target = false;
}

//=============================================================================
// Initialize the TankHead.
// Post: returns true if successful, false if failed
//=============================================================================
bool TankHead::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}


//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void TankHead::update(float frameTime)
{
	D3DXVECTOR2 mouseLocation(input->getMouseX(), input->getMouseY());
	
	D3DXVECTOR2* deltaVector = new D3DXVECTOR2;
	
	D3DXVec2Normalize(deltaVector,(const D3DXVECTOR2*)new D3DXVECTOR2(mouseLocation.x - getCenterX(), mouseLocation.y - getCenterY()));


	float headAngle = acos(D3DXVec2Dot(deltaVector, &D3DXVECTOR2(0, -1)));

	spriteData.angle = headAngle;

	if (deltaVector->x < 0)
		spriteData.angle = 2 * PI - spriteData.angle;

	

	delete deltaVector;
    Entity::update(frameTime);
	   
    //spriteData.x += velocity.x * frameTime;
    //velocity.x = 0;
    //spriteData.y += velocity.y * frameTime;
    //velocity.y = 0;


    //// wrap around screen
    //if (spriteData.x > GAME_WIDTH)                  // if off screen right
    //    spriteData.x = -tankHeadNS::WIDTH;              // position off screen left
    //else if (spriteData.x < -tankHeadNS::WIDTH)         // else if off screen left
    //    spriteData.x = GAME_WIDTH;                  // position off screen right
    //if (spriteData.y < -tankHeadNS::HEIGHT)             // if off screen top
    //    spriteData.y = GAME_HEIGHT;                 // position off screen bottom
    //else if (spriteData.y > GAME_HEIGHT)            // else if off screen bottom
    //    spriteData.y = -tankHeadNS::HEIGHT;             // position off screen top
}

