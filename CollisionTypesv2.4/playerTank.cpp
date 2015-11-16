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
	spriteData.width = playerTankNS::WIDTH;           // size of PlayerTank1
	spriteData.height = playerTankNS::HEIGHT;
	spriteData.x = playerTankNS::X;                   // location on screen
	spriteData.y = playerTankNS::Y;
	spriteData.rect.bottom = playerTankNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = playerTankNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y

	currentFrame = 0;
	radius = playerTankNS::WIDTH/2.0;                 // collision radius
	collision = false;
	collisionType = entityNS::BOX;
	target = false;

	spriteData.width = playerTankNS::WIDTH;           // size of Ship1
	spriteData.height = playerTankNS::HEIGHT;
	spriteData.x = playerTankNS::X;                   // location on screen
	spriteData.y = playerTankNS::Y;
	spriteData.rect.bottom = playerTankNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = playerTankNS::WIDTH;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================

bool PlayerTank::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

bool PlayerTank::initializeHead(Game *gamePtr, int width, int height, int ncols,
								TextureManager *textureM, TextureManager *textureZ)
{
	bool result = head.initialize(gamePtr, width, height, ncols, textureM);

	for (int i = 0; i < MAX_PLAYER_SHOTS; i++)
		head.bullet[i].initialize(gamePtr, bulletNS::WIDTH, bulletNS::HEIGHT, 0, textureZ);

	if (result)
	{
		head.setScale(spriteData.scale);
		head.setCurrentFrame(0);

		for (int i = 0; i < MAX_PLAYER_SHOTS; i++)
			head.bullet[i].setScale(spriteData.scale);

	}

	return result;
}

void PlayerTank::draw()
{
	Image::draw();

	head.draw();

	for (int i = 0; i < MAX_PLAYER_SHOTS; i++)
		head.bullet[i].draw();
}


//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void PlayerTank::update(float frameTime)
{
	Entity::update(frameTime);

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
	spriteData.y += velocity.y * frameTime;
	/*velocity.y = 0;
	velocity.x = 0;*/


	head.setX(spriteData.x);
	head.setY(spriteData.y);

	head.update(frameTime);

	for (int i = 0; i < MAX_PLAYER_SHOTS; i++)
		head.bullet[i].update(frameTime);


	//// wrap around screen
	//if (spriteData.x > GAME_WIDTH)                  // if off screen right
	//    spriteData.x = -playerTankNS::WIDTH;              // position off screen left
	//else if (spriteData.x < -playerTankNS::WIDTH)         // else if off screen left
	//    spriteData.x = GAME_WIDTH;                  // position off screen right
	//if (spriteData.y < -playerTankNS::HEIGHT)             // if off screen top
	//    spriteData.y = GAME_HEIGHT;                 // position off screen bottom
	//else if (spriteData.y > GAME_HEIGHT)            // else if off screen bottom
	//    spriteData.y = -playerTankNS::HEIGHT;             // position off screen top
}

//void PlayerTank::circleBounce(VECTOR2 &collisionVector, Entity &ent)
//{
//	VECTOR2 Vdiff = ent.getVelocity() - velocity;
//	VECTOR2 cUV = collisionVector;              // collision unit vector
//	Graphics::Vector2Normalize(&cUV);
//	float cUVdotVdiff = Graphics::Vector2Dot(&cUV, &Vdiff);
//	float massRatio = 1.0f;
//	//if (getMass() != 0)
//		massRatio *= (ent.getMass() / (getMass() + ent.getMass()));
//
//	// If entities are already moving apart then bounce must
//	// have been previously called and they are still colliding.
//	// Move entities apart along collisionVector
//	if(cUVdotVdiff > 0)
//	{
//		setX(getX() - cUV.x * massRatio);
//		setY(getY() - cUV.y * massRatio);
//	}
//	else 
//	{
//		//deltaV += ((massRatio * cUVdotVdiff) * cUV);
//		deltaV += 100 * cUV;
//	
//		//velocity *= -1;
//	}
//}

void PlayerTank::circleBounce(VECTOR2 &collisionVector, Entity &ent, float frameTime)
{
	VECTOR2 Vdiff = ent.getVelocity() - velocity;
	VECTOR2 cUV = collisionVector;              // collision unit vector

	Graphics::Vector2Normalize(&Vdiff);
	Graphics::Vector2Normalize(&cUV);
	float cUVdotVdiff = Graphics::Vector2Dot(&cUV, &Vdiff);
	float massRatio = 1.0f;
	if (getMass() != 0)
		massRatio *= (ent.getMass() / (getMass() + ent.getMass()));
	if(massRatio < 0.1f)
		massRatio = 0.1f;

	// Move entities out of collision along collision vector
	VECTOR2 cv;
	int count=10;   // loop limit
	/*do
	{
	setX(getX() - cUV.x);
	setY(getY() - cUV.y);
	rotatedBoxReady = false;
	count--;
	} while( this->collidesWith(ent, cv) && count);*/

	// bounce
	//deltaV -= ((massRatio * cUVdotVdiff) 10 * cUV;
	/*velocity.x = 0;
	velocity.y = 0;*/
	//deltaV -= collisionVector;

	VECTOR2 uvelocity = velocity/playerTankNS::SPEED;

	float cosine = Graphics::Vector2Dot(&uvelocity, &cUV);
	if (  .9 < abs(cosine) && abs(cosine) < 1.1 || -.9 > cosine && cosine > -1.1  )
	{
		if (velocity.x == 0 && velocity.y == 0)
			velocity = collisionVector;
		else
			velocity *= -1;
	}
	else
		velocity = -collisionVector;

	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;
}