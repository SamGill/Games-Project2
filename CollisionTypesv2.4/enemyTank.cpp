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
	mass = 1;
	numBulletsFired = 0;
}

bool enemyTank::initialize(Game *gamePtr, int width, int height, int ncols,
						   TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

bool enemyTank::initializeBullets(Game *gamePtr, int width, int height, int ncols,
								  TextureManager *textureM)
{
	for (int i = 0; i < NUM_ENEMY_BULLETS; i++)
	{
		if (!bullets[i].initialize(gamePtr, width, height, ncols, textureM))
			return false;
		bullets[i].setScale(spriteData.scale);

	}

	return testRay.initialize(gamePtr, width, height, ncols, textureM);
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


void enemyTank::draw()
{
	Entity::draw();

	for (int i = 0; i < NUM_ENEMY_BULLETS; i++)
		bullets[i].draw();
}
//=============================================================================
// update
// typically called once per frame
// frameTime is used to regulate the speed of movement and animation
//=============================================================================
void enemyTank::update(float frameTime)
{
	VECTOR2 foo = velocity*frameTime*speed;
	/*if (getPositionX() + Image::getWidth()*Image::getScale() > GAME_WIDTH)
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
	}*/

	velocity = D3DXVECTOR2(0,0);

	incPosition(foo);

	Image::setX(getPositionX());
	Image::setY(getPositionY());
	Entity::update(frameTime);

	if (getX() > GAME_WIDTH - getWidth() * getScale())
	{
		setX(GAME_WIDTH - getWidth() * getScale());
	}
	if (getX() < 0)
	{
		setX(0);
	}
	if (getY() < 0)
	{
		setY(0);
	}

	if (getY() > (GAME_HEIGHT - getHeight() * getScale()))
	{
		setY(GAME_HEIGHT - getHeight() * getScale());
	}

	for (int i = 0; i < NUM_ENEMY_BULLETS; i++)
	{
		bullets[i].update(frameTime);
	}
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

	D3DXVECTOR2 targetLocation(targetEntity.getCenterPoint());


	D3DXVec2Normalize(&angleVector,(const D3DXVECTOR2*)new D3DXVECTOR2(targetLocation.x - getCenterX(), targetLocation.y - getCenterY()));


	float headAngle = acos(D3DXVec2Dot(&angleVector, &D3DXVECTOR2(0, -1)));

	spriteData.angle = headAngle;

	if (angleVector.x < 0)
		spriteData.angle = 2 * PI - spriteData.angle;

}

void enemyTank::fireAtPlayer()
{
	VECTOR2 distanceVec = getCenterPoint()-targetEntity.getCenterPoint();
	float distance = D3DXVec2Length(&distanceVec);

	if (distance < 200 && visible)
		fireBullet(distanceVec);
}


void enemyTank::fireBullet(VECTOR2 angle)
{

	if (shotBuffer.canFire(2) && numBulletsFired < NUM_ENEMY_BULLETS)
	{
		shotBuffer.start();
		angle *= -1;
		float nozzleRadius = getWidth()/2 * getScale();

		Graphics::Vector2Normalize(&angle);

		bullets[numBulletsFired].setX(getCenterX() + angle.x * nozzleRadius);
		bullets[numBulletsFired].setY(getCenterY() + angle.y * nozzleRadius);
		bullets[numBulletsFired].setRadians(spriteData.angle);
		bullets[numBulletsFired].setVelocity(angle * bulletNS::SPEED);
		bullets[numBulletsFired].setVisible(true);	
	}
	//This is the case where the player has too many bullets on the screen, but he should be able to fire based on the time buffer.


	organizeBullets();
}

void enemyTank::ai(float time, Entity &t)
{ 

	targetEntity = t;
	fireAtPlayer();
	//vectorTrack();
	//deltaTrack();
	//evade();
	return;
}