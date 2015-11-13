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
	gamestates = intro;
	timeInState = 0;
	isMusicPlaying = false;

#pragma region game_textures

	if (!enemyTankTexture.initialize(graphics, ENEMY_TANK))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if (!tankBodyTexture.initialize(graphics, TANK_BODY))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if (!tankHeadTexture.initialize(graphics, TANK_HEAD))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if (!bulletTexture.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if (!playerTank.initialize(this, playerTankNS::WIDTH, playerTankNS::HEIGHT, 0, &tankBodyTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing body"));

	if (!enemyTank.initialize(this, enemyTankNS::WIDTH, enemyTankNS::HEIGHT, 0, &enemyTankTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing body"));

	//SPLASH SCREEN
	if (!splashScreenTexture.initialize(graphics,SPLASH_SCREEN))
        throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing splash screen texture"));
	if (!splashScreen.initialize(graphics, splashScreenTexture.getWidth(),splashScreenTexture.getHeight(),0, &splashScreenTexture))
		throw(GameError(gameErrorNS::WARNING, "Splashscreen not initialized"));
	splashScreen.setX(0);
	splashScreen.setY(0);

	//GAME OVER SCREEN
	if(!gameOverTexture.initialize(graphics, GAME_OVER))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game over screen texture"));
	if(!gameOverScreen.initialize(graphics, gameOverTexture.getWidth(), gameOverTexture.getHeight(), 0, &gameOverTexture))
		throw(GameError(gameErrorNS::WARNING, "Game over screen not initialized"));
	gameOverScreen.setX(0);
	gameOverScreen.setY(0);

	//MENU SCREEN
	if(!gameMenuTexture.initialize(graphics, MENU_SCREEN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game menu screen texture"));
	if(!gameMenuScreen.initialize(graphics, gameMenuTexture.getWidth(), gameMenuTexture.getHeight(), 0, &gameMenuTexture))
		throw(GameError(gameErrorNS::WARNING, "Game menu screen not initialized"));
	gameMenuScreen.setX(0);
	gameMenuScreen.setY(0);

	//CHEAT CODE SCREEN
	if(!cheatCodeTexture.initialize(graphics, CHEAT_SCREEN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cheat code screen texture"));
	if(!cheatCodeScreen.initialize(graphics, cheatCodeTexture.getWidth(), cheatCodeTexture.getHeight(), 0, &cheatCodeTexture))
		throw(GameError(gameErrorNS::WARNING, "Cheat code screen not initialized"));
	cheatCodeScreen.setX(0);
	cheatCodeScreen.setY(0);

	//enemyTank.setCurrentFrame(0);
	enemyTank.setX(GAME_WIDTH/2 - 100);
	enemyTank.setY(GAME_HEIGHT/2 - 100);
	enemyTank.setScale(.20f);
	enemyTank.setPosition(VECTOR2(100,100));

	playerTank.setCurrentFrame(0);
	playerTank.setScale(.20f);
	
	playerTank.setX(GAME_WIDTH/2);
	playerTank.setY(GAME_HEIGHT/2);
	playerTank.setPosition(VECTOR2(GAME_WIDTH/2,GAME_HEIGHT/2));
	
	if (!playerTank.initializeHead(this, tankHeadNS::WIDTH,tankHeadNS::HEIGHT,0, &tankHeadTexture, &bulletTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing head"));

	playerTank.setCollisionType(entityNS::ROTATED_BOX);

#pragma endregion

	// init sound system
    audio = new Audio();

    if (*WAVE_BANK != '\0' && *SOUND_BANK != '\0')  // if sound files defined
    {
        if( FAILED( hr = audio->initialize() ) )
        {
            if( hr == HRESULT_FROM_WIN32( ERROR_FILE_NOT_FOUND ) )
                throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize sound system because media file not found."));
            else
                throw(GameError(gameErrorNS::FATAL_ERROR, "Failed to initialize sound system."));
        }
    }

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

	//patternsteps
	patternStepIndex = 0;
	for (int i = 0; i< maxPatternSteps; i++)
	{
		patternSteps[i].initialize(&enemyTank);
		patternSteps[i].setActive();
	}

	patternSteps[0].setAction(RIGHT);
	patternSteps[0].setTimeForStep(2);
	patternSteps[1].setAction(DOWN);
	patternSteps[1].setTimeForStep(2);
	patternSteps[2].setAction(LEFT);
	patternSteps[2].setTimeForStep(2);
	patternSteps[3].setAction(UP);
	patternSteps[3].setTimeForStep(2);
	patternSteps[4].setAction(TRACK);
	patternSteps[4].setTimeForStep(5);

	return;
}

//=============================================================================
// Update all game items
//=============================================================================

 void CollisionTypes::gameStatesUpdate()
{
	timeInState += frameTime;

	if(gamestates == intro && timeInState > 3)
	{
		gamestates = gameMenu;
		timeInState = 0;
	}
	if(gamestates == gameMenu)
	{
		//If "Enter" is pressed, start game
		if(input->wasKeyPressed(0x0D))
		{
			gamestates = level_one;
			timeInState = 0;
		}
		//If "C" is pressed, go to cheat code screen
		if(input->wasKeyPressed(0x43))
		{
			gamestates = cheatCodes;
			timeInState = 0;
		}

		//If "E" is pressed, exit the game
		if(input->wasKeyPressed(0x45))
		{
			PostQuitMessage(0);
		}
	}
	if(gamestates == cheatCodes)
	{
		//If "U" was pressed, give unlimited health
		if(input->wasKeyPressed(0x55))
		{
			//Give ulimited health
			;
		}
		//If "W" was pressed, give all weapons
		if(input->wasKeyPressed(0x57))
		{
			//Give all weapons
			;
		}
		//If "2" was pressed, jump to level 2
		if(input->wasKeyPressed(0x32))
		{
			//Jump to level 2
			;
		}
		//If "ESC" was pressed, go back to main menu
		if(input->wasKeyPressed(ESC_KEY))
		{
			gamestates = gameMenu;
			timeInState = 0;
		}
	}

	//Moves to game over screen, but only for testing
	if(gamestates == level_one && timeInState > 10)
	{
		//gamestates = gameover;
		timeInState = 0;
	}

	//Restarts game back to menu 
	if(gamestates == gameover)
	{
		if(input->wasKeyPressed(0x52))
		{
			gamestates = intro;
			timeInState = 0;
		}
		else if(input->wasKeyPressed(0x45))
		{
			PostQuitMessage(0);
		}
	}
}

void CollisionTypes::update()
{
	gameStatesUpdate();
	switch (gamestates)
	{
	case intro:
		break;
	case gameMenu:
		break;
	case cheatCodes:
		break;
	case level_one:
/*		if(input->isKeyDown(TANK_UP_KEY))
			playerTank.move_up();
		if(input->isKeyDown(TANK_DOWN_KEY))
			playerTank.move_down();
		if (input->isKeyDown(TANK_LEFT_KEY))   
			playerTank.move_left();
		if (input->isKeyDown(TANK_RIGHT_KEY))  
			playerTank.move_right();*/
		if(!isMusicPlaying)
		{
			audio->playCue(MAIN_MUSIC);
			isMusicPlaying = true;
		}

		if(input->isKeyDown(TANK_UP_KEY))
            playerTank.forward();
        if(input->isKeyDown(TANK_DOWN_KEY))
            playerTank.reverse();
        playerTank.rotate(playerTankNS::NONE);
		if (input->isKeyDown(TANK_LEFT_KEY))   // if turn ship0 left
            playerTank.rotate(playerTankNS::LEFT);
        if (input->isKeyDown(TANK_RIGHT_KEY))  // if turn ship0 right
            playerTank.rotate(playerTankNS::RIGHT);

		if (input->getMouseLButton())
			playerTank.fireBullet();
		playerTank.update(frameTime);
		enemyTank.update(frameTime);
		break;
	case level_two:
		break;
	case victory:
		break;
	case gameover:
		break;
	default:
		break;
	}
	//playerTankHead.update(frameTime);

}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void CollisionTypes::ai()
{
	enemyTank.ai(frameTime, playerTank);

	float distance = D3DXVec2Length(&(enemyTank.getCenterPoint()-playerTank.getCenterPoint()));

	if(distance < 200.0f)
	{
		enemyTank.ai(frameTime, playerTank);
		patternStepIndex = 4;
		patternSteps[4].initialize(&enemyTank);
		patternSteps[4].setActive();
	}
	else if(patternStepIndex == maxPatternSteps - 1)
	{
		enemyTank.ai(frameTime, playerTank);
		for (int i = 0; i < maxPatternSteps - 1; i++)
		{
			patternSteps[i].initialize(&enemyTank);
			patternSteps[i].setActive();
		}
		patternStepIndex = 0;
	}
	
	if (patternSteps[patternStepIndex].isFinished())
		patternStepIndex++;
	patternSteps[patternStepIndex].update(frameTime);
}

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
	switch (gamestates)
	{
	case intro:
		splashScreen.draw();
		break;
	case cheatCodes:
		cheatCodeScreen.draw();
		break;
	case gameMenu:
		gameMenuScreen.draw();
		break;
	case level_one:
		enemyTank.draw();
		playerTank.draw();
		break;
	case level_two:
		break;
	case victory:
		break;
	case gameover:
		gameOverScreen.draw();
		break;
	default:
		break;
	}
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
	enemyTankTexture.onLostDevice();
	gameOverTexture.onLostDevice();
	bulletTexture.onLostDevice();
	splashScreenTexture.onLostDevice();
	gameMenuTexture.onLostDevice();
	cheatCodeTexture.onLostDevice();
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
	enemyTankTexture.onResetDevice();
	gameOverTexture.onResetDevice();
	bulletTexture.onResetDevice();
	splashScreenTexture.onResetDevice();
	gameMenuTexture.onResetDevice();
	cheatCodeTexture.onResetDevice();
	Game::resetAll();
    return;
}
