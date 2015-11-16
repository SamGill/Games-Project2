#include "murray.h"

//=============================================================================
// default constructor
//=============================================================================
murray::murray() : Entity()
{
	spriteData.width = murrayNS::WIDTH;           // size of Wall1
	spriteData.height = murrayNS::HEIGHT;
	spriteData.x = murrayNS::X;                   // location on screen
	spriteData.y = murrayNS::Y;
	spriteData.rect.bottom = murrayNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = murrayNS::WIDTH;
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
bool murray::initialize(Game *gamePtr, int width, int height, int ncols,
						  TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}
