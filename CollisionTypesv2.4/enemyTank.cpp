#include "enemyTank.h"

//=============================================================================
// default constructor
//=============================================================================
enemyTank::enemyTank() : Entity()
{
    spriteData.width = enemyTankNS::WIDTH;           
    spriteData.height = enemyTankNS::HEIGHT;
    spriteData.x = enemyTankNS::X;                   // location on screen
    spriteData.y = enemyTankNS::Y;
    spriteData.rect.bottom = enemyTankNS::HEIGHT/2;    // rectangle to select parts of an image
    spriteData.rect.right = enemyTankNS::WIDTH;
    
	velocity = D3DXVECTOR2(0,0);
    startFrame = 0;              // first frame of ship animation
    endFrame     = 0;              // last frame of ship animation
    currentFrame = startFrame;
    radius = enemyTankNS::WIDTH/2.0;                 // collision radius
    collision = false;
    collisionType =entityNS::BOX;// entityNS::CIRCLE;
    target = false;
	edge.bottom = -enemyTankNS::HEIGHT/2;
	spriteData.scale = 1;
	active = true;
	speed = 50;
}

bool enemyTank::initialize(Game *gamePtr, int width, int height, int ncols,
    TextureManager *textureM)
{
    return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void enemyTank::setInvisible()
{
	Image::setVisible(false);
	active = false;
}

void enemyTank::setVisible()
{
	Image::setVisible(true);
	active = true;
}

//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void enemyTank::update(float frameTime)
{
	VECTOR2 foo = velocity*frameTime*speed;
	if (getPositionX() + Image::getWidth()*Image::getScale() > GAME_WIDTH)
	{
		setPosition(D3DXVECTOR2(0,getPositionY()));
	}
	if (getPositionX() < 0)
	{
		setPosition(D3DXVECTOR2(GAME_WIDTH-Image::getWidth()*Image::getScale(),getPositionY()));
	}
	if (getPositionY() + Image::getHeight()*Image::getScale() > GAME_HEIGHT)
	{
		setPosition(D3DXVECTOR2(getPositionX(),0));
	}
	if (getPositionY() < 0)
	{
		setPosition(D3DXVECTOR2(getPositionX(),GAME_WIDTH-Image::getHeight()*Image::getScale()));
	}

	velocity = D3DXVECTOR2(0,0);
	incPosition(foo);
	Image::setX(getPositionX());
	Image::setY(getPositionY());
    Entity::update(frameTime);
}

void enemyTank::evade()
{
	//add code here
	VECTOR2 vel = D3DXVECTOR2(1,1);
	VECTOR2 targetCenter = targetEntity.getCenterPoint();
	if(getCenterPoint().y <= targetCenter.y)
		vel.y = -1;
	if(getCenterPoint().x <= targetCenter.x)
		vel.x = -1;
	setVelocity(vel);

	return;
}

void enemyTank::deltaTrack()
{
	//add code here
	VECTOR2 vel = D3DXVECTOR2(1,1);
	VECTOR2 targetCenter = targetEntity.getCenterPoint();
	if(getCenterPoint().y <= targetCenter.y)
		vel.y = -1;
	if(getCenterPoint().x <= targetCenter.x)
		vel.x = -1;
	setVelocity(-vel);
	return;

}
void enemyTank::vectorTrack()
{
	//add code here
	VECTOR2 vel = getCenterPoint() - targetEntity.getCenterPoint();
	if(vel.x == 0 && vel.y == 0)
		return;

	VECTOR2* foo = D3DXVec2Normalize(&vel, &vel);
	setVelocity(-vel);
	
}

void enemyTank::ai(float time, Entity &t)
{ 
	targetEntity = t;
	//vectorTrack();
	//deltaTrack();
	//evade();
	return;
}