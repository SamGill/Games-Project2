#ifndef _ENEMYTANK_H                 // Prevent multiple definitions if this 
#define _ENEMYTANK_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class enemyTank;

#include "entity.h"
#include "constants.h"

namespace enemyTankNS
{
    const int WIDTH = 512;                   // image width
    const int HEIGHT = 512;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float ROTATION_RATE = (float)PI/3; // radians per second
    const float SPEED = 100;                // 100 pixels per second
    enum DIRECTION {NONE, LEFT, RIGHT};     // rotation direction
}

// inherits from Entity class
class enemyTank : public Entity
{
private:
    enemyTankNS::DIRECTION direction;    // direction of rotation
    bool collision;                 // true when ship is colliding
    bool target;                    // true if target, false if ship

public:
    // constructor
    enemyTank();

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
    void rotate(enemyTankNS::DIRECTION dir) {direction = dir;}

    // move forward
    void forward()
    {
        velocity.x = (float)cos(spriteData.angle) * enemyTankNS::SPEED;
        velocity.y = (float)sin(spriteData.angle) * enemyTankNS::SPEED;
    }

    // move in reverse
    void reverse()
    {
        velocity.x = -(float)cos(spriteData.angle) * enemyTankNS::SPEED;
        velocity.y = -(float)sin(spriteData.angle) * enemyTankNS::SPEED;
    }
};
#endif

