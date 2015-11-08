// Programming 2D Games
// Copyright (c) 2012 by: 
// Charles Kelly
// Collision Types ship.h v1.0

#ifndef _PLAYERTANK_H                 // Prevent multiple definitions if this 
#define _PLAYERTANK_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class PlayerTank;

#include "entity.h"
#include "constants.h"

namespace playerTankNS
{
    const int WIDTH = 64;                   // image width
    const int HEIGHT = 64;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float ROTATION_RATE = (float)PI/3; // radians per second
    const float SPEED = 100;                // 100 pixels per second
    enum DIRECTION {NONE, LEFT, RIGHT};     // rotation direction
}

// inherits from Entity class
class PlayerTank : public Entity
{
private:
    playerTankNS::DIRECTION direction;    // direction of rotation
    bool collision;                 // true when ship is colliding
    bool target;                    // true if target, false if ship

public:
    // constructor
    PlayerTank();

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

    // direction of rotation force
    //void rotate(playerTankNS::DIRECTION dir) {direction = dir;}

    // move forward

	void move_up()
	{
		velocity.y = -playerTankNS::SPEED;
	}

	void move_right()
	{

	}

	void move_left()
	{

	}

	void move_down()
	{

	}

    void forward()
    {
        velocity.x = (float)cos(spriteData.angle) * playerTankNS::SPEED;
        velocity.y = (float)sin(spriteData.angle) * playerTankNS::SPEED;
    }

    // move in reverse
    void reverse()
    {
        velocity.x = -(float)cos(spriteData.angle) * playerTankNS::SPEED;
        velocity.y = -(float)sin(spriteData.angle) * playerTankNS::SPEED;
    }
};
#endif

