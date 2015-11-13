#pragma once
#define WIN32_LEAN_AND_MEAN

class TankHead;

#include "entity.h"
#include "constants.h"
#include "bullet.h"
#include "shotBuffer.h"
#include <algorithm>

namespace tankHeadNS
{
    const int WIDTH =  512;                   // image width
    const int HEIGHT = 512;                  // image height
    const int X = GAME_WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2;
    const float ROTATION_RATE = (float)PI/3; // radians per second
    const float SPEED = 100;                // 100 pixels per second
}

// inherits from Entity class
class TankHead : public Entity
{
private:
    //tankHeadNS::DIRECTION direction;    // direction of rotation
    bool collision;                 // true when ship is colliding
    bool target;                    // true if target, false if ship
	
	ShotBuffer shotBuffer;
	unsigned int numBulletsFired;
	VECTOR2 angleVector; //This vector is used for making the bullets go in the right direction

	//Function sorts the bullets in such a way that visible bullets are more early on in the list and 
	//updates numBulletsFired to accurately say how many bullets are visible on the screen at once
	void organizeBullets()
	{
		numBulletsFired = 0;
		for (int i = 0; i < MAX_PLAYER_SHOTS; i++)
		{
			if (bullet[i].getVisible())
			{
				//puts the bullet in the earliest spot that isn't a visible as well.
				std::swap(bullet[numBulletsFired], bullet[i]);
				numBulletsFired++;
			}
			
		}
	}
	
public:
	Bullet bullet[MAX_PLAYER_SHOTS];

    // constructor
    TankHead();

    // inherited member functions
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);

    // Set collision Boolean
    void setCollision(bool c)
    {collision = c;}

    // Set collision type (NONE, CIRCLE, BOX, ROTATED_BOX)
    virtual void setCollisionType(entityNS::COLLISION_TYPE ctype)
    {collisionType = ctype;}

    // Set RECT structure used for BOX and ROTATED_BOX collision detection.
    void setEdge(RECT e) {edge = e;}

    // Set target
    void setTarget(bool t) {target = t;}

    // Get collision
    bool getCollision() {return collision;}

    // Get collision type
    entityNS::COLLISION_TYPE getCollisionType() {return collisionType;}
	    
	void fireBullet();
};