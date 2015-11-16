#include "crackOne.h"

//=============================================================================
// default constructor
//=============================================================================
crackOne::crackOne() : Entity()
{
	spriteData.width = crackOneTankNS::WIDTH;           // size of PlayerTank1
	spriteData.height = crackOneTankNS::HEIGHT;
	spriteData.x = crackOneTankNS::X;                   // location on screen
	spriteData.y = crackOneTankNS::Y;
	spriteData.rect.bottom = crackOneTankNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = crackOneTankNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y

	currentFrame = 0;
	radius = crackOneTankNS::WIDTH/2.0;                 // collision radius
	collision = false;
	collisionType = entityNS::BOX;
	target = false;

	spriteData.width = crackOneTankNS::WIDTH;           // size of Ship1
	spriteData.height = crackOneTankNS::HEIGHT;
	spriteData.x = crackOneTankNS::X;                   // location on screen
	spriteData.y = crackOneTankNS::Y;
	spriteData.rect.bottom = crackOneTankNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = crackOneTankNS::WIDTH;
}

//=============================================================================
// Initialize the Ship.
// Post: returns true if successful, false if failed
//=============================================================================

bool crackOne::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

bool crackOne::initializeHead(Game *gamePtr, int width, int height, int ncols,
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

void crackOne::draw()
{
	Image::draw();

	//head.draw();

	for (int i = 0; i < MAX_PLAYER_SHOTS; i++)
		head.bullet[i].draw();
}


//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void crackOne::update(float frameTime)
{

    switch (direction)                          // rotate ship
    {
    case crackOneTankNS::LEFT:
        spriteData.angle -= frameTime * crackOneTankNS::ROTATION_RATE;  // rotate left
        break;							
    case crackOneTankNS::RIGHT:			
        spriteData.angle += frameTime * crackOneTankNS::ROTATION_RATE;  // rotate right
        break;
    }

	spriteData.x += velocity.x * frameTime;
	spriteData.y += velocity.y * frameTime;
	velocity.y = 0;
	velocity.x = 0;


	head.setX(spriteData.x);
	head.setY(spriteData.y);

	head.update(frameTime);

	for (int i = 0; i < MAX_PLAYER_SHOTS; i++)
		head.bullet[i].update(frameTime);

	Entity::update(frameTime);
}

