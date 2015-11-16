#pragma once
#define WIN32_LEAN_AND_MEAN

class Bullet;

#include "entity.h"
#include "constants.h"

namespace bulletNS
{
	const int WIDTH =  32;                   // image width
	const int HEIGHT = 32;                  // image height
	const int X = 0;  // location on screen
	const int Y = 0;
	const float ROTATION_RATE = (float)PI/3; // radians per second
	const float SPEED = 270;                // 100 pixels per second
}

// inherits from Entity class
class Bullet : public Entity
{
private:
	//bulletNS::DIRECTION direction;    // direction of rotation
	bool collision;                 // true when ship is colliding
	bool target;                    // true if target, false if ship
public:
	// constructor
	Bullet();

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
	//void rotate(bulletNS::DIRECTION dir) {direction = dir;}

	void circleBounce(VECTOR2 &collisionVector, Entity &ent);


	void reflectVelocity(VECTOR2 colV)
	{
		collision = true;

		if (colV.x != 0)
			velocity.x *= -1;
		else
			velocity.y *= -1;
	};

};