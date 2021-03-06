#pragma once
#define WIN32_LEAN_AND_MEAN

class murray;

#include "entity.h"
#include "constants.h"

namespace murrayNS
{
    const int WIDTH =  32;                   // image width
    const int HEIGHT = 32;                  // image height
    const int X = GAME_WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2;
}

// inherits from Entity class
class murray : public Entity
{
private:
    bool collision;                 // true when ship is colliding
public:
    // constructor
    murray();

    // inherited member functions
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    //void update(float frameTime);

    // Set collision Boolean
    void setCollision(bool c)
    {collision = c;}

    // Set collision type (NONE, CIRCLE, BOX, ROTATED_BOX)
    virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)
    {collisionType = ctype;}

    // Set RECT structure used for BOX and ROTATED_BOX collision detection.
    void setEdge(RECT e) {edge = e;}

    // Get collision
    bool getCollision() {return collision;}

    // Get collision type
    entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}
	    
};