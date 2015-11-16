#include "gill.h"

//=============================================================================
// default constructor
//=============================================================================
gill::gill() : Entity()
{
	spriteData.width = gillNS::WIDTH;           // size of Wall1
	spriteData.height = gillNS::HEIGHT;
	spriteData.x = gillNS::X;                   // location on screen
	spriteData.y = gillNS::Y;
	spriteData.rect.bottom = gillNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = gillNS::WIDTH;
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
bool gill::initialize(Game *gamePtr, int width, int height, int ncols,
						  TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
