#ifndef _ENEMYTANK_H                 // Prevent multiple definitions if this 
#define _ENEMYTANK_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class enemyTank;

#include "entity.h"
#include "constants.h"
#include "graphics.h"
#include "bullet.h"
#include "shotBuffer.h"
#include "patternStep.h"

#define maxPatternSteps 5

namespace enemyTankNS
{
    const int WIDTH = 512;                   // image width
    const int HEIGHT = 512;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float SPEED_X = 0;                
	const float SPEED_Y = -0;
	const float ROTATION_RATE = (float)PI/3; // radians per second
	enum DIRECTION {NONE, LEFT, RIGHT};     // rotation direction
}

// inherits from Entity class
class enemyTank : public Entity
{
private:
	enemyTankNS::DIRECTION direction;    // direction of rotation
    bool collision;                 
    bool target;  
	int directionX;
	int directionY;
	VECTOR2 velocity;
	VECTOR2 dir;
	float speed;
	Entity targetEntity;
	//void vectorTrack();
	//void deltaTrack();
	//void evade();
	VECTOR2 angleVector;
	Bullet bullets[NUM_ENEMY_BULLETS];
	Bullet testRay;
	ShotBuffer shotBuffer;
	int numBulletsFired;
	void organizeBullets()
	{
		numBulletsFired = 0;
		for (int i = 0; i < NUM_ENEMY_BULLETS; i++)
		{
			if (bullets[i].getVisible())
			{
				//puts the bullet in the earliest spot that isn't a visible as well.
				std::swap(bullets[numBulletsFired], bullets[i]);
				numBulletsFired++;
			}
			
		}
	}
public:
    // constructor
    enemyTank();

    // inherited member functions
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
	virtual void draw();
	bool initializeBullets(Game *gamePtr, int width, int height, int ncols,
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

	void setInvisible();

	void setVisible();

	void setVelocity(VECTOR2 v) {velocity = v;}

	void rotate(enemyTankNS::DIRECTION dir) {direction = dir;}

	VECTOR2 getVelocity() { return velocity; }

	void ai(float time, Entity &t);


	Bullet* getBullets() {return bullets; }

	void vectorTrack();
	void deltaTrack();
	void evade();
	void fireAtPlayer();
	void fireBullet(VECTOR2);
};
#endif
