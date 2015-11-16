// Programming 2D Games
// Copyright (c) 2012 by: 
// Charles Kelly
// CollisionTypes ship.cpp v1.0

#include "bullet.h"
#include "constants.h"

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
	edge = BULLET_RECTANGLE;
	currentFrame = 0;
	radius = bulletNS::WIDTH/2.0;                 // collision radius
	collision = false;
	//collisionType = entityNS::ROTATED_BOX;
	collisionType = entityNS::CIRCLE;

	mass = 300.0f;

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

	if (D3DXVec2Length(&velocity) < bulletNS::SPEED)
	{
		D3DXVec2Normalize(&velocity, &velocity);
		velocity *= bulletNS::SPEED;
	}
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


void Bullet::circleBounce(VECTOR2 &collisionVector, Entity &ent)
{
    VECTOR2 Vdiff = ent.getVelocity() - velocity;
    VECTOR2 cUV = collisionVector;              // collision unit vector
    Graphics::Vector2Normalize(&cUV);
    float cUVdotVdiff = Graphics::Vector2Dot(&cUV, &Vdiff);
    float massRatio = 2.0f;
    if (getMass() != 0)
        massRatio *= (ent.getMass() / (getMass() + ent.getMass()));

    // If entities are already moving apart then bounce must
    // have been previously called and they are still colliding.
    // Move entities apart along collisionVector
    if(cUVdotVdiff > 0)
    {
        setX(getX() - cUV.x * massRatio);
        setY(getY() - cUV.y * massRatio);
    }
    else 
        deltaV += ((massRatio * cUVdotVdiff) * cUV);
}