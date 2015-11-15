// Programming 2D Games
// Copyright (c) 2012 by: 
// Charles Kelly
// CollisionTypes ship.cpp v1.0

#include "tankHead.h"
#include "shotBuffer.h"



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

	currentFrame = 0;
	radius = tankHeadNS::WIDTH/2.0;                 // collision radius
	collision = false;
	collisionType = entityNS::BOX;
	target = false;

	//keeps track of how many bullets are still being fired
	numBulletsFired = 0;
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

	D3DXVec2Normalize(&angleVector,(const D3DXVECTOR2*)new D3DXVECTOR2(mouseLocation.x - getCenterX(), mouseLocation.y - getCenterY()));


	float headAngle = acos(D3DXVec2Dot(&angleVector, &D3DXVECTOR2(0, -1)));

	spriteData.angle = headAngle;

	if (angleVector.x < 0)
		spriteData.angle = 2 * PI - spriteData.angle;

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

void TankHead::fireBullet()
{
	if (shotBuffer.canFire(SHOT_TIME_BUFFER) && numBulletsFired < MAX_PLAYER_SHOTS)
	{
		shotBuffer.start();

		float nozzleRadius = getWidth()/2 * getScale();

		bullet[numBulletsFired].setX(getCenterX() + angleVector.x * nozzleRadius);
		bullet[numBulletsFired].setY(getCenterY() + angleVector.y * nozzleRadius);
		bullet[numBulletsFired].setRadians(spriteData.angle);
		bullet[numBulletsFired].setVelocity(angleVector * bulletNS::SPEED);
		bullet[numBulletsFired].setVisible(true);	
	}
	//This is the case where the player has too many bullets on the screen, but he should be able to fire based on the time buffer.
	

	organizeBullets();
}