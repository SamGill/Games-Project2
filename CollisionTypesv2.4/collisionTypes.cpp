// Programming 2D Games
// Copyright (c) 2011, 2012 by: 
// Charles Kelly
// Collision types demo
// Press '1', '2' or '3' to select collision type for ship.

#include "collisionTypes.h"

//=============================================================================
// Constructor
//=============================================================================
CollisionTypes::CollisionTypes()
{
	menuOn = true;
}

//=============================================================================
// Destructor
//=============================================================================
CollisionTypes::~CollisionTypes()
{
	releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void CollisionTypes::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

	if (!tankBodyTexture.initialize(graphics, TANK_BODY))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if (!tankHeadTexture.initialize(graphics, TANK_HEAD))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if (!playerTank.initialize(this, playerTankNS::WIDTH, playerTankNS::HEIGHT, 0, &tankBodyTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing body"));

	playerTank.setScale(.25f);
	
	playerTank.setX(GAME_WIDTH/2);
	playerTank.setY(GAME_HEIGHT/2);
	
	if (!playerTank.initializeHead(this, tankHeadNS::WIDTH,tankHeadNS::HEIGHT,0, &tankHeadTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing head"));

	playerTank.setCollisionType(entityNS::ROTATED_BOX);

#pragma region Original Game Textures
	// menu texture
	if (!menuTexture.initialize(graphics,MENU_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu texture"));
	// main game textures
	if (!gameTextures.initialize(graphics,TEXTURES_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));

	// menu image
	if (!menu.initialize(graphics,0,0,0,&menuTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing menu"));

	// rectangle
	if (!rectangle.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing rectangle"));
	rectangle.setFrames(RECTANGLE_START_FRAME, RECTANGLE_END_FRAME);
	rectangle.setCurrentFrame(RECTANGLE_START_FRAME);
	rectangle.setX(GAME_WIDTH/4);
	rectangle.setY(GAME_HEIGHT/2);
	rectangle.setCollisionType(entityNS::ROTATED_BOX);
	// edge specifies the collision box relative to the center of the entity.
	rectangle.setEdge(COLLISION_RECTANGLE);
	rectangle.setDegrees(45);
	rectangle.setTarget(true);

	// square
	if (!square.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing square"));
	square.setFrames(SQUARE_START_FRAME, SQUARE_END_FRAME);
	square.setCurrentFrame(SQUARE_START_FRAME);
	square.setX(GAME_WIDTH/2);
	square.setY(GAME_HEIGHT/2);
	square.setCollisionType(entityNS::BOX);
	// edge specifies the collision box relative to the center of the entity.
	square.setEdge(COLLISION_BOX);
	square.setTarget(true);

	// circle
	if (!circle.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing circle"));
	circle.setFrames(CIRCLE_START_FRAME, CIRCLE_END_FRAME);
	circle.setCurrentFrame(CIRCLE_START_FRAME);
	circle.setX(GAME_WIDTH - GAME_WIDTH/4);
	circle.setY(GAME_HEIGHT/2);
	circle.setCollisionType(entityNS::CIRCLE);
	circle.setCollisionRadius(COLLISION_RADIUS);
	circle.setTarget(true);

	// ship
	if (!ship.initialize(this, shipNS::WIDTH, shipNS::HEIGHT, TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
	ship.setFrames(SHIP_START_FRAME, SHIP_END_FRAME);
	ship.setCurrentFrame(SHIP_START_FRAME);
	ship.setX(GAME_WIDTH/2);
	ship.setY(GAME_HEIGHT/4);
	ship.setCollisionType(entityNS::CIRCLE);
	// edge specifies the collision box relative to the center of the entity.
	ship.setEdge(COLLISION_BOX);
	ship.setCollisionRadius(COLLISION_RADIUS);

	// line
	if (!line.initialize(graphics, shipNS::WIDTH, shipNS::HEIGHT, TEXTURE_COLS, &gameTextures))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing line"));
	line.setFrames(LINE_START_FRAME, LINE_END_FRAME);
	line.setCurrentFrame(LINE_START_FRAME);
	line.setScale(LINE_SCALE);
	line.setX(0);
	line.setY(0);
#pragma endregion Original Game Textures

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void CollisionTypes::update()
{

	if(input->isKeyDown(TANK_UP_KEY))
		playerTank.move_up();
	if(input->isKeyDown(TANK_DOWN_KEY))
		playerTank.move_down();
	if (input->isKeyDown(TANK_LEFT_KEY))   
		playerTank.move_left();
	if (input->isKeyDown(TANK_RIGHT_KEY))  
		playerTank.move_right();

	playerTank.update(frameTime);
	//playerTankHead.update(frameTime);


}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void CollisionTypes::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void CollisionTypes::collisions()
{
	collisionVector.x = 0;      // clear collision vector
	collisionVector.y = 0;

	// if collision between ship and targets
	ship.setCollision(false);
	rectangle.setCollision(false);
	square.setCollision(false);
	circle.setCollision(false);
	if(ship.collidesWith(rectangle, collisionVector))
	{
		ship.setCollision(true);
		rectangle.setCollision(true);
		lineEnds[1].x = rectangle.getCollisionCenter()->x;
		lineEnds[1].y = rectangle.getCollisionCenter()->y;
	}
	if(ship.collidesWith(square, collisionVector))
	{
		//ship.bounce(collisionVector, square);
		ship.setCollision(true);
		square.setCollision(true);
		lineEnds[1].x = square.getCollisionCenter()->x;
		lineEnds[1].y = square.getCollisionCenter()->y;
	}
	if(ship.collidesWith(circle, collisionVector))
	{
		ship.setCollision(true);
		circle.setCollision(true);
		lineEnds[1].x = circle.getCollisionCenter()->x;
		lineEnds[1].y = circle.getCollisionCenter()->y;
	}
	// Initialize line endpoints for drawing collision vector
	lineEnds[0].x = ship.getCollisionCenter()->x;
	lineEnds[0].y = ship.getCollisionCenter()->y;

}

//=============================================================================
// Render game items
//=============================================================================
void CollisionTypes::render()
{
	float angle;
	graphics->spriteBegin();                // begin drawing sprites
	//if(menuOn)
	//	menu.draw();
	//else
	//{
	//	if(rectangle.getCollision())        // if collision with rectangle
	//		rectangle.draw(graphicsNS::RED & graphicsNS::ALPHA50);   // draw target in semitransparent Red
	//	else
	//		rectangle.draw(graphicsNS::GREEN);
	//	if(square.getCollision())           // if collision with square
	//		square.draw(graphicsNS::RED & graphicsNS::ALPHA50);   // draw target in semitransparent Red
	//	else
	//		square.draw(graphicsNS::YELLOW);
	//	if(circle.getCollision())           // if collision with circle
	//		circle.draw(graphicsNS::RED & graphicsNS::ALPHA50);   // draw target in semitransparent Red
	//	else
	//		circle.draw(graphicsNS::ORANGE);

	//	ship.draw();

	//	if(ship.getCollision())             // if ship is colliding
	//	{
	//		// if collision with square and ship collision type is BOX
	//		if(square.getCollision() && ship.getCollisionType() == entityNS::BOX)
	//		{
	//			angle = ship.getRadians();
	//			ship.setRadians(0);
	//			// draw semi-transparent square over ship
	//			square.draw(ship.getSpriteData(), graphicsNS::RED & graphicsNS::ALPHA50);
	//			ship.setRadians(angle);
	//		}
	//		else
	//		{
	//			// if ship collision type is ROTATED_BOX
	//			if(ship.getCollisionType() == entityNS::ROTATED_BOX)
	//				// draw semi-transparent rectangle over ship
	//					rectangle.draw(ship.getSpriteData(), graphicsNS::RED & graphicsNS::ALPHA50);
	//			// if ship collision type is BOX
	//			else if(ship.getCollisionType() == entityNS::BOX)
	//				// draw semi-transparent box over ship
	//				square.draw(ship.getSpriteData(), graphicsNS::RED & graphicsNS::ALPHA50);
	//			// if ship collision type is CIRCLE
	//			else if(ship.getCollisionType() == entityNS::CIRCLE)
	//				// draw semi-transparent circle over ship
	//				circle.draw(ship.getSpriteData(), graphicsNS::RED & graphicsNS::ALPHA50);
	//		}
	//		// Angle of line
	//		lineRadians = std::atan2(lineEnds[1].y - lineEnds[0].y, lineEnds[1].x - lineEnds[0].x);
	//		line.setRadians(lineRadians);
	//		// Line length
	//		AxBx = lineEnds[0].x - lineEnds[1].x;
	//		AyBy = lineEnds[0].y - lineEnds[1].y;
	//		lineLength = std::sqrt( AxBx*AxBx + AyBy*AyBy);
	//		// Adjust displayed line length with spriteData.rect
	//		RECT rect = line.getSpriteDataRect();
	//		rect.right = (LONG)(LINE_LENGTH + lineLength/LINE_SCALE);
	//		line.setSpriteDataRect(rect);
	//		// Set position of line start
	//		line.setX(lineEnds[0].x-LINE_LENGTH*LINE_SCALE);
	//		line.setY(lineEnds[0].y-LINE_LENGTH*LINE_SCALE);
	//		line.draw(graphicsNS::CYAN);
	//	}
	//	else    // not colliding
	//	{
	//		// if ship collision type is ROTATED_BOX
	//		if(ship.getCollisionType() == entityNS::ROTATED_BOX)
	//			// draw semi-transparent rectangle over ship
	//				rectangle.draw(ship.getSpriteData(), graphicsNS::ALPHA50);
	//		// if ship collision type is BOX
	//		else if(ship.getCollisionType() == entityNS::BOX)
	//		{
	//			angle = ship.getRadians();
	//			ship.setRadians(0);
	//			// draw semi-transparent box over ship
	//			square.draw(ship.getSpriteData(), graphicsNS::ALPHA50);
	//			ship.setRadians(angle);
	//		}
	//		// if ship collision type is CIRCLE
	//		else if(ship.getCollisionType() == entityNS::CIRCLE)
	//			// draw semi-transparent circle over ship
	//			circle.draw(ship.getSpriteData(), graphicsNS::ALPHA50);
	//	}
	//}
	ship.draw();
	playerTank.draw();


	graphics->spriteEnd();                  // end drawing sprites
}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void CollisionTypes::releaseAll()
{
	menuTexture.onLostDevice();
	gameTextures.onLostDevice();
	tankBodyTexture.onLostDevice();
	tankHeadTexture.onLostDevice();
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void CollisionTypes::resetAll()
{
	gameTextures.onResetDevice();
	menuTexture.onResetDevice();
	tankBodyTexture.onResetDevice();
	tankHeadTexture.onResetDevice();
	Game::resetAll();
	return;
}
