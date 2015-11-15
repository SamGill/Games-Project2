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

#pragma region Level One Walls
	//Texture initialization
	if (!wallLgHzTexture.initialize(graphics,WALL_LONG_HORIZONTAL))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));
	if (!wallShortHzTexture.initialize(graphics,WALL_SHORT_HORIZONTAL))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));
	if (!wallLgVtTexture.initialize(graphics,WALL_LONG_VERTICAL))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));
	if (!wallShortVtTexture.initialize(graphics,WALL_SHORT_VERTICAL))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	for(int i = 0; i < 4; i++)
		if (!wallLgHzScreen[i].initialize(this, 320, 32, 0, &wallLgHzTexture))
			throw(GameError(gameErrorNS::WARNING, "wall long horizontal not initialized"));
	if (!wallLgVtScreen.initialize(this, wallLgVtTexture.getWidth(),wallLgVtTexture.getHeight(),0, &wallLgVtTexture))
		throw(GameError(gameErrorNS::WARNING, "wall long vertical not initialized"));
	for(int i = 0; i < 4; i++)
		if (!wallShortHzScreen[i].initialize(this, wallShortHzTexture.getWidth(),wallShortHzTexture.getHeight(),0, &wallShortHzTexture))
			throw(GameError(gameErrorNS::WARNING, "wall short horizontal not initialized"));
	for(int i = 0; i < 2; i++)
		if (!wallShortVtScreen[i].initialize(this, wallShortVtTexture.getWidth(),wallShortVtTexture.getHeight(),0, &wallShortVtTexture))
			throw(GameError(gameErrorNS::WARNING, "wall short vertical not initialized"));

	
#pragma endregion Level One Walls


	if (!enemyTankTexture.initialize(graphics, ENEMY_TANK))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if (!tankBodyTexture.initialize(graphics, TANK_BODY))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if (!tankHeadTexture.initialize(graphics, TANK_HEAD))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if (!bulletTexture.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if (!wallTexture.initialize(graphics, WALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));



	if (!playerTank.initialize(this, playerTankNS::WIDTH, playerTankNS::HEIGHT, 0, &tankBodyTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing body"));

	for (int i = 0; i < MAX_ENEMY_TANKS; i++)
		if (!enemyTanks[i].initialize(this, enemyTankNS::WIDTH, enemyTankNS::HEIGHT, 0, &enemyTankTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing body"));

	if (!wall.initialize(this, wallNS::WIDTH, wallNS::HEIGHT, 0, &wallTexture))
		throw(GameError(gameErrorNS::WARNING, "wall not initialized"));

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

	//Placement of walls

	//Long horizontal walls
	wallLgHzScreen[0].setX(wallOneX);
	wallLgHzScreen[0].setY(wallOneY);

	wallLgHzScreen[1].setX(wallNineX);
	wallLgHzScreen[1].setY(wallNineY);

	wallLgHzScreen[2].setX(wallElevenX);
	wallLgHzScreen[2].setY(wallElevenY);

	wallLgHzScreen[3].setX(wallFourX);
	wallLgHzScreen[3].setY(wallFourY);

	//Short vertical walls
	wallShortVtScreen[0].setX(wallTwoX);
	wallShortVtScreen[0].setY(wallTwoY);

	wallShortVtScreen[1].setX(wallFiveX);
	wallShortVtScreen[1].setY(wallFiveY);

	//Short horizontal walls
	wallShortHzScreen[0].setX(wallSixX);
	wallShortHzScreen[0].setY(wallSixY);

	wallShortHzScreen[1].setX(wallSevenX);
	wallShortHzScreen[1].setY(wallSevenY);

	wallShortHzScreen[2].setX(wallEightX);
	wallShortHzScreen[2].setY(wallEightY);

	wallShortHzScreen[3].setX(wallTwelveX);
	wallShortHzScreen[3].setY(wallTwelveY);


	//Wall long horizontal collision box
	for(int i = 0; i < 4; i++)
	{
		wallLgHzScreen[i].setCollisionType(entityNS::BOX);
		wallLgHzScreen[i].setEdge(WALL_LONG_HZ_RECT);
	}

	//Wall short vertical collision box
	for (int i = 0; i < 2; i++)
	{
		wallShortVtScreen[i].setCollisionType(entityNS::BOX);
		wallShortVtScreen[i].setEdge(WALL_SHORT_VT_RECT);
	}

	//Wall short horizontal collision box
	for (int i = 0; i < 4; i++)
	{
		wallShortHzScreen[i].setCollisionType(entityNS::BOX);
		wallShortHzScreen[i].setEdge(WALL_SHORT_HZ_RECT);
	}


	wall.setScale(.5f);
	wall.setCollisionType(entityNS::BOX);

	RECT collision  = {-45,-10,45,10};
	wall.setEdge(WALL_RECTANGLE);
	wall.setX(400);
	wall.setY(400);

	//playerTank.getBullets()[0].setEdge(collision);

	//wall.setEdge();

	for (int i = 0; i < MAX_ENEMY_TANKS; i++)
	{
		enemyTanks[i].setPositionX(GAME_WIDTH/(i + 1));
		enemyTanks[i].setPositionY(GAME_HEIGHT/7);
		enemyTanks[i].setScale(.25f);
		enemyTanks[i].setEdge(TANK_RECTANGLE);
	}

	playerTank.setCurrentFrame(0);
	playerTank.setScale(.20f);

	playerTank.setX(levelOnePlayerX);
	playerTank.setY(levelOnePlayerY);


	if (!playerTank.initializeHead(this, tankHeadNS::WIDTH,tankHeadNS::HEIGHT,0, &tankHeadTexture, &bulletTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing head"));

	playerTank.setCollisionType(entityNS::ROTATED_BOX);
	playerTank.setEdge(TANK_RECTANGLE);

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


	//patternsteps
	//	patternStepIndex = 0;
	//	for (int i = 0; i < maxPatternSteps; i++)
	//	{
	//		patternSteps[i].initialize(&enemyTanks[0]);
	//		patternSteps[i].setActive();
	//	}
	//
	//	patternSteps[0].setAction(RIGHT);
	//	patternSteps[0].setTimeForStep(2);
	//	patternSteps[1].setAction(DOWN);
	//	patternSteps[1].setTimeForStep(2);
	//<<<<<<< HEAD
	//
	//	patternSteps[2].setAction(LEFT);
	//	patternSteps[2].setTimeForStep(2);
	//
	//	patternSteps[3].setAction(UP);
	//	patternSteps[3].setTimeForStep(2);
	//	patternSteps[4].setAction(EVADE);
	//	patternSteps[4].setTimeForStep(3);
	//
	//	/*patternSteps[2].setAction(TRACK);
	//	patternSteps[2].setTimeForStep(4);
	//	patternSteps[3].setAction(NONE);
	//	patternSteps[3].setTimeForStep(2);*/
	//=======
	//	patternSteps[2].setAction(LEFT);
	//	patternSteps[2].setTimeForStep(2);
	//	patternSteps[3].setAction(UP);
	//	patternSteps[3].setTimeForStep(2);
	//	patternSteps[4].setAction(TRACK);
	//	patternSteps[4].setTimeForStep(5);
	//>>>>>>> origin/master
	//
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
		for (int i = 0; i < MAX_ENEMY_TANKS; i++)
			enemyTanks[i].update(frameTime);
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
}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void CollisionTypes::ai()
{
	//if (playerTank.isFiring() == false)
	//	enemyTanks[0].ai(frameTime, playerTank);
	//else
	//{
	//	enemyTanks[0].ai(frameTime, playerTank.getBullets()[0]);
	//	patternStepIndex = 4;
	//	patternSteps[4].initialize(&enemyTanks[0]);
	//	patternSteps[4].setActive();
	//}
	///*if (patternStepIndex == maxPatternSteps)
	//return;*/
	//if ( (patternStepIndex == maxPatternSteps - 1 && !playerTank.isFiring()) || patternStepIndex == maxPatternSteps)
	//{
	//	for (int i = 0; i < maxPatternSteps - 1; i++)
	//	{
	//		patternSteps[i].initialize(&enemyTanks[0]);
	//		
	//			enemyTank.ai(frameTime, playerTank);

	//		float distance = D3DXVec2Length(&(enemyTank.getCenterPoint()-playerTank.getCenterPoint()));

	//		if(distance < 200.0f)
	//		{
	//			enemyTank.ai(frameTime, playerTank);
	//			patternStepIndex = 4;
	//			patternSteps[4].initialize(&enemyTank);
	//			patternSteps[4].setActive();
	//		}
	//		else if(patternStepIndex == maxPatternSteps - 1)
	//		{
	//			enemyTank.ai(frameTime, playerTank);
	//			for (int i = 0; i < maxPatternSteps - 1; i++)
	//			{
	//				patternSteps[i].initialize(&enemyTank);
	//				>>>>>>> origin/master
	//					patternSteps[i].setActive();
	//			}
	//			patternStepIndex = 0;
	//		}
	//		<<<<<<< HEAD
	//			=======

	//			>>>>>>> origin/master
	//			if (patternSteps[patternStepIndex].isFinished())
	//				patternStepIndex++;

	//		patternSteps[patternStepIndex].update(frameTime);
	//	}
}
//=============================================================================
// Handle collisions
//=============================================================================
void CollisionTypes::collisions()
{
	Bullet* bullets = playerTank.getBullets();

	collisionVector.x = 0;      // clear collision vector
	collisionVector.y = 0;

	playerTank.setCollision(false);

	for (int i = 0; i < MAX_ENEMY_TANKS; i++)
	{
		if (playerTank.collidesWith(enemyTanks[i], collisionVector))
		{

			playerTank.setVelocity(VECTOR2(-collisionVector));
			enemyTanks[i].setVelocity(VECTOR2(collisionVector));
			playerTank.setCollision(true);

		}
	}

	if (playerTank.collidesWith(wall, collisionVector))
	{

		playerTank.setCollision(true);
		playerTank.bounce(collisionVector, wall);
	}



	for (int i = 0; i < MAX_PLAYER_SHOTS; i++)
	{
		//save some comparisons
		if (bullets[i].getVisible() == false)
		{
			bullets[i].setCollision(false);
			break;
		}

		for (int j = 0; j < 4; j++)
		{
			if (bullets[i].collidesWith(wallLgHzScreen[j], collisionVector))
			{
				if (bullets[i].getCollision() == false)
				{
					bullets[i].setCollision(true);

					VECTOR2 currentVelocity = bullets[i].getVelocity();

					if (collisionVector.x != 0)
						currentVelocity.x *= -1;
					else
						currentVelocity.y *= -1;

					bullets[i].setVelocity(currentVelocity);
				}
			}
			else 
				bullets[i].setCollision(false);
		}

		for (int j = 0; j < MAX_ENEMY_TANKS; j++)
		{
			if (enemyTanks[j].getVisible() && bullets[i].collidesWith(enemyTanks[j], collisionVector))
			{
				float currentHealth = enemyTanks[j].getHealth();
				enemyTanks[j].setHealth(enemyTanks[j].getHealth() - 20.0f);
				if (enemyTanks[j].getHealth() == 0.0f)
					enemyTanks[j].setInvisible();

				bullets[i].setVisible(false);


			}
		}
	}

	for(int i = 0; i < 4; i++)
	{
		if(playerTank.collidesWith(wallLgHzScreen[i], collisionVector))
		{
			playerTank.setCollision(true);
			playerTank.bounce(collisionVector, wallLgHzScreen[i]);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		if(playerTank.collidesWith(wallShortVtScreen[i], collisionVector))
		{
			playerTank.setCollision(true);
			playerTank.bounce(collisionVector, wallShortVtScreen[i]);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (playerTank.collidesWith(wallShortHzScreen[i], collisionVector))
		{
			playerTank.setCollision(true);
			playerTank.bounce(collisionVector, wallShortHzScreen[i]);
		}
	}
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
		for (int i = 0; i < 4; i++)
		{
			wallLgHzScreen[i].draw();
		}
		for (int i = 0; i < 2; i++)
		{
			wallShortVtScreen[i].draw();
		}
		for (int i = 0; i < 3; i++)
		{
			wallShortHzScreen[i].draw();
		}
		//for (int i = 0; i < MAX_ENEMY_TANKS; i++)
			//enemyTanks[i].draw();
		playerTank.draw();
		//wall.draw();
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
	wallTexture.onLostDevice();
	gameOverTexture.onLostDevice();
	bulletTexture.onLostDevice();
	splashScreenTexture.onLostDevice();
	gameMenuTexture.onLostDevice();
	cheatCodeTexture.onLostDevice();
	wallLgHzTexture.onLostDevice();
	wallLgVtTexture.onLostDevice();
	wallShortHzTexture.onLostDevice();
	wallShortVtTexture.onLostDevice();
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
	wallTexture.onResetDevice();
	gameOverTexture.onResetDevice();
	bulletTexture.onResetDevice();
	splashScreenTexture.onResetDevice();
	gameMenuTexture.onResetDevice();
	cheatCodeTexture.onResetDevice();
	wallLgHzTexture.onResetDevice();
	wallLgVtTexture.onResetDevice();
	wallShortHzTexture.onResetDevice();
	wallShortVtTexture.onResetDevice();
	Game::resetAll();
	return;
}
