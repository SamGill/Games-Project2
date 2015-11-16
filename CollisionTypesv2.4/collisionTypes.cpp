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
	//gamestates = intro;
	gamestates = level_two;

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

	if (!wallLgHzScreen.initialize(this, 320, 32, 0, &wallLgHzTexture))
		throw(GameError(gameErrorNS::WARNING, "wall long horizontal not initialized"));
	if (!wallLgVtScreen.initialize(this, wallLgVtTexture.getWidth(),wallLgVtTexture.getHeight(),0, &wallLgVtTexture))
		throw(GameError(gameErrorNS::WARNING, "wall long vertical not initialized"));
	if (!wallShortHzScreen.initialize(this, wallShortHzTexture.getWidth(),wallShortHzTexture.getHeight(),0, &wallShortHzTexture))
		throw(GameError(gameErrorNS::WARNING, "wall short horizontal not initialized"));
	if (!wallShortVtScreen.initialize(this, wallShortVtTexture.getWidth(),wallShortVtTexture.getHeight(),0, &wallShortVtTexture))
		throw(GameError(gameErrorNS::WARNING, "wall short vertical not initialized"));




	//Placement of walls
	wallLgHzScreen.setX(wallOneX);
	wallLgHzScreen.setY(wallOneY);


#pragma endregion Level One Walls

#pragma region Level Two Walls

	if (!circleWallTexture.initialize(graphics, WALL_CIRCLE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if (!circleWall.initialize(this, circleWallTexture.getWidth(), circleWallTexture.getHeight(), 0, &circleWallTexture))
		throw(GameError(gameErrorNS::WARNING, "wall circle not initialized"));

	for (int i = 0; i < NUM_LVL_TWO_HZ_WALL; i++)
	{
		if (!wallLvl2Horizontal[i].initialize(this, wallShortHzTexture.getWidth(),wallShortHzTexture.getHeight(), 0, &wallShortHzTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

		wallLvl2Horizontal[i].setEdge(WALL_SHORT_HZ_RECT);
	}

	for (int i = 0; i < NUM_LVL_TWO_VT_WALL; i++)
	{
		if (!wallLvl2Vertical[i].initialize(this, wallShortVtTexture.getWidth(),wallShortVtTexture.getHeight() - 20, 0, &wallShortVtTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

		wallLvl2Vertical[i].setEdge(WALL_SHORT_VT_RECT);
	}

	wallLvl2Horizontal[0].setX(0);
	wallLvl2Horizontal[0].setY(2 * GAME_HEIGHT/3);

	wallLvl2Horizontal[1].setX(GAME_WIDTH - wallLvl2Horizontal[1].getWidth());
	wallLvl2Horizontal[1].setY(GAME_HEIGHT/3);

	wallLvl2Horizontal[2].setX(GAME_WIDTH/2 + circleWall.getWidth()/2 - 10);
	wallLvl2Horizontal[2].setY(GAME_HEIGHT/2);


	wallLvl2Vertical[0].setX(GAME_WIDTH/2);
	wallLvl2Vertical[0].setY(0);

	wallLvl2Vertical[1].setX(GAME_WIDTH/5);
	wallLvl2Vertical[1].setY(GAME_HEIGHT - wallLvl2Vertical[1].getHeight());

	wallLvl2Vertical[2].setX(GAME_WIDTH/2 - 10);
	wallLvl2Vertical[2].setY(GAME_HEIGHT/2 + circleWall.getHeight()/2 + 40);



	circleWall.setX(GAME_WIDTH/2 - circleWall.getWidth()/2 - 10);
	circleWall.setY(GAME_HEIGHT/2 - circleWall.getHeight()/3 - 10);
	circleWall.setCollisionType(entityNS::CIRCLE);
	circleWall.setCollisionRadius(circleWallTexture.getHeight()/2);
#pragma endregion

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
	{
		if (!enemyTanks[i].initialize(this, enemyTankNS::WIDTH, enemyTankNS::HEIGHT, 0, &enemyTankTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing body"));

		enemyTanks[i].setScale(.20f);


		if (!enemyTanks[i].initializeBullets(this, bulletNS::WIDTH, bulletNS::HEIGHT, 0, &bulletTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing enemy bullet"));

	}

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

	//Wall long horizontal collision box
	wallLgHzScreen.setCollisionType(entityNS::BOX);
	wallLgHzScreen.setEdge(WALL_LONG_HZ_RECT);



	for (int i = 0; i < MAX_ENEMY_TANKS; i++)
	{
		enemyTanks[i].setEdge(TANK_RECTANGLE);
		enemyTanks[i].setPosition(VECTOR2(-1,-1));
	}

	enemyTanks[0].setPositionX(2 * GAME_WIDTH/3);
	enemyTanks[0].setPositionY(GAME_HEIGHT/5);

	enemyTanks[1].setPositionX(GAME_WIDTH/2 - enemyTanks[1].getWidth());
	enemyTanks[1].setPositionY(GAME_HEIGHT/3);

	enemyTanks[2].setPositionX(GAME_WIDTH/2 - enemyTanks[1].getWidth());
	enemyTanks[2].setPositionY(GAME_HEIGHT - enemyTanks[2].getWidth() * enemyTanks[2].getScale());

	enemyTanks[3].setPositionX(GAME_WIDTH/3);
	enemyTanks[3].setPositionY(2 * GAME_HEIGHT/3);

	enemyTanks[4].setPositionX(GAME_WIDTH - 4 * enemyTanks[4].getWidth() * enemyTanks[4].getScale());
	enemyTanks[4].setPositionY(GAME_HEIGHT -3 * enemyTanks[4].getWidth() * enemyTanks[4].getScale());

	enemyTanks[5].setPositionX(GAME_WIDTH  - 5 * enemyTanks[5].getWidth() * enemyTanks[5].getScale() - 10);
	enemyTanks[5].setPositionY(GAME_HEIGHT - 2 * enemyTanks[5].getWidth() * enemyTanks[5].getScale() + 50);

	enemyTanks[6].setPositionX(GAME_WIDTH  - enemyTanks[6].getWidth());
	enemyTanks[6].setPositionY(GAME_HEIGHT - enemyTanks[6].getWidth());


	/*enemyTanks[3].setPositionX(
	enemyTanks[3].setPositionY(*/

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

	initializeLvlTwoPatterns();


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
			gamestates = level_two;

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
		if(!isMusicPlaying)
		{
			//audio->playCue(MAIN_MUSIC);
			isMusicPlaying = true;
		}

		playerTank.setVelocity(VECTOR2(0,0));
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
	for (int i = 0; i < MAX_ENEMY_TANKS; i++)
	{
		enemyTanks[i].ai(frameTime, playerTank);
		performEnemyTankPatternStep(i);
	}

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

	//playerTank.setCollision(false);

	for (int i = 0; i < MAX_ENEMY_TANKS; i++)
	{
		if (playerTank.collidesWith(enemyTanks[i], collisionVector))
		{
			playerTank.setVelocity(VECTOR2(-collisionVector));
			enemyTanks[i].setVelocity(VECTOR2(collisionVector));
			playerTank.setCollision(true);
		}
	}


	for (int i = 0; i < MAX_PLAYER_SHOTS; i++)
	{
		//save some comparisons
		if (bullets[i].getVisible() == false)
			break;

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


	if(playerTank.collidesWith(wallLgHzScreen, collisionVector))
	{
		playerTank.setCollision(true);
		playerTank.bounce(collisionVector, wallLgHzScreen);
	}

	/*for (int i = 0; i < MAX_PLAYER_SHOTS; i++)
	{
	if (bullets[i].collidesWith(wallLgHzScreen, collisionVector))
	{
	bullets[i].reflectVelocity(collisionVector);			
	}
	}*/


	switch (gamestates)
	{
	case level_two:


		//First Check for all player Tank collisions
		for (int i = 0; i < NUM_LVL_TWO_HZ_WALL; i++)
		{
			if (playerTank.collidesWith(wallLvl2Horizontal[i], collisionVector))
			{
				playerTank.setCollision(true);
				playerTank.bounce(collisionVector, wallLvl2Horizontal[i]);
			}

			for (int j = 0; j < MAX_ENEMY_TANKS; j++)
			{
				if (enemyTanks[j].collidesWith(wallLvl2Horizontal[i], collisionVector))
				{
					enemyTanks[j].setCollision(true);
					enemyTanks[j].bounce(collisionVector, wallLvl2Horizontal[i]);
				}
			}
		}
		for (int i = 0; i < NUM_LVL_TWO_VT_WALL; i++)
		{
			if (playerTank.collidesWith(wallLvl2Vertical[i], collisionVector))
			{
				playerTank.setCollision(true);
				playerTank.bounce(collisionVector, wallLvl2Vertical[i]);
			}

			for (int j = 0; j < MAX_ENEMY_TANKS; j++)
			{
				if (enemyTanks[j].collidesWith(wallLvl2Vertical[i], collisionVector))
				{
					enemyTanks[j].setCollision(true);
					enemyTanks[j].bounce(collisionVector, wallLvl2Vertical[i]);
				}
			}
		}

		//if (playerTank.collidesWith(circleWall, collisionVector))
		//{
		//	playerTank.setCollision(true);
		//	playerTank.circleBounce(collisionVector, circleWall, frameTime);
		//	//playerTank.bounce(collisionVector, circleWall);
		//}
		//else
		//	playerTank.setCollision(false);


		//next check for all bullet collisoins
		for (int i = 0; i < MAX_PLAYER_SHOTS; i++)
		{
			//if this statements is true, the rest should all be invisible as well
			/*if (bullets[i].getVisible() == false)
			{
			for (int j = i; j < MAX_PLAYER_SHOTS; j++)
			bullets[j].setCollision(false);
			break;
			}*/

			//for (int i = 0; i < MAX_ENEMY_TANKS; i++)




			if (bullets[i].collidesWith(wallLgHzScreen, collisionVector))
			{
				if (bullets[i].getCollision() == false)
				{
					bullets[i].reflectVelocity(collisionVector);
					bullets[i].setCollision(true);
				}
				continue;			
			}

			//Collision with the circle wall
			//if (bullets[i].collidesWith(circleWall, collisionVector))
			//{
			//	if (bullets[i].getCollision() == false)
			//	{

			//		/*VECTOR2 currentVelocity = bullets[i].getVelocity();
			//		collisionVector *= -1;
			//		bool changeXDirection = collisionVector.x < 0 && currentVelocity.x > 0 || collisionVector.x > 0 && currentVelocity.x < 0;
			//		bool changeYDirection = collisionVector.y < 0 && currentVelocity.y > 0 || collisionVector.y > 0 && currentVelocity.y < 0;
			//		if (changeXDirection)
			//		currentVelocity.x *= -1;
			//		if (changeYDirection)
			//		currentVelocity.y *= -1;
			//		bullets[i].setVelocity(currentVelocity);*/

			//		//D3DXVec2Normalize(&collisionVector, &collisionVector);
			//		/*VECTOR2 oldVelocity = bullets[i].getVelocity();

			//		float cosineOfAngle = D3DXVec2Dot(&collisionVector, &oldVelocity)/(D3DXVec2Length(&collisionVector) * D3DXVec2Length(&oldVelocity));*/

			//		bullets[i].circleBounce(collisionVector, circleWall);


			//		bullets[i].setCollision(true);
			//	}
			//	continue;
			//}

			for (int j = 0; j < NUM_LVL_TWO_HZ_WALL; j++)
			{
				if (bullets[i].collidesWith(wallLvl2Horizontal[j], collisionVector))
				{
					if (bullets[i].getCollision() == false)
					{
						bullets[i].reflectVelocity(collisionVector);
						bullets[i].setCollision(true);
					}
					continue;
				}
			}

			for (int j = 0; j < NUM_LVL_TWO_VT_WALL; j++)
			{
				if (bullets[i].collidesWith(wallLvl2Vertical[j], collisionVector))
				{
					if (bullets[i].getCollision() == false)
					{
						bullets[i].reflectVelocity(collisionVector);
						bullets[i].setCollision(true);
					}
					continue;
				}
			}

			bullets[i].setCollision(false);
		}
	}

	//#pragma region Original code
	//	collisionVector.x = 0;      // clear collision vector
	//	collisionVector.y = 0;
	//
	//	// if collision between ship and targets
	//	ship.setCollision(false);
	//	rectangle.setCollision(false);
	//	square.setCollision(false);
	//	circle.setCollision(false);
	//	if(ship.collidesWith(rectangle, collisionVector))
	//	{
	//		ship.setCollision(true);
	//		rectangle.setCollision(true);
	//		lineEnds[1].x = rectangle.getCollisionCenter()->x;
	//		lineEnds[1].y = rectangle.getCollisionCenter()->y;
	//	}
	//	if(ship.collidesWith(square, collisionVector))
	//	{
	//		//ship.bounce(collisionVector, square);
	//		ship.setCollision(true);
	//		square.setCollision(true);
	//		lineEnds[1].x = square.getCollisionCenter()->x;
	//		lineEnds[1].y = square.getCollisionCenter()->y;
	//	}
	//	if(ship.collidesWith(circle, collisionVector))
	//	{
	//		ship.setCollision(true);
	//		circle.setCollision(true);
	//		lineEnds[1].x = circle.getCollisionCenter()->x;
	//		lineEnds[1].y = circle.getCollisionCenter()->y;
	//	}
	//	// Initialize line endpoints for drawing collision vector
	//	lineEnds[0].x = ship.getCollisionCenter()->x;
	//	lineEnds[0].y = ship.getCollisionCenter()->y;
	//#pragma endregion 
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
		wallLgHzScreen.draw();
		//for (int i = 0; i < MAX_ENEMY_TANKS; i++)
		//enemyTanks[i].draw();
		playerTank.draw();
		break;
	case level_two:
		playerTank.draw();
		wallLgHzScreen.draw();
		for (int i = 0; i < NUM_LVL_TWO_HZ_WALL; i++)
			wallLvl2Horizontal[i].draw();
		for (int i = 0; i < NUM_LVL_TWO_VT_WALL; i++)
			wallLvl2Vertical[i].draw();

		for (int i = 0; i < MAX_ENEMY_TANKS; i++)
			enemyTanks[i].draw();
		//circleWall.draw();
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
	circleWallTexture.onLostDevice();
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
	circleWallTexture.onResetDevice();
	Game::resetAll();
	return;
}


void CollisionTypes::performEnemyTankPatternStep(int index)
{
	//enemyTanks[index].ai(frameTime, playerTank);

	if (patternStepIndexLvlTwo[index] == maxPatternSteps)
	{
		for (int i = 0; i < maxPatternSteps; i++)
		{
			patternStepsLvl2[index][i].initialize(&enemyTanks[index]);
			patternStepsLvl2[index][i].setActive();
		}
		patternStepIndexLvlTwo[index] = 0;
	}

	patternStepsLvl2[index][patternStepIndexLvlTwo[index]].update(frameTime);


	if (patternStepsLvl2[index][patternStepIndexLvlTwo[index]].isFinished())
		patternStepIndexLvlTwo[index]++;

}

void CollisionTypes::initializeLvlTwoPatterns()
{
	for (int i = 0; i < MAX_ENEMY_TANKS; i++)
	{
		patternStepIndexLvlTwo[i] = 0;

		for (int j = 0; j < maxPatternSteps; j++)
		{
			patternStepsLvl2[i][j].initialize(&enemyTanks[i]);
			patternStepsLvl2[i][j].setActive();
		}
	}

	patternStepsLvl2[0][0].setAction(RIGHT);
	patternStepsLvl2[0][0].setTimeForStep(2);
	patternStepsLvl2[0][1].setAction(UP);
	patternStepsLvl2[0][1].setTimeForStep(2);
	patternStepsLvl2[0][2].setAction(LEFT);
	patternStepsLvl2[0][2].setTimeForStep(2);
	patternStepsLvl2[0][3].setAction(DOWN);
	patternStepsLvl2[0][3].setTimeForStep(2);

	patternStepsLvl2[1][0].setAction(RIGHT);
	patternStepsLvl2[1][0].setTimeForStep(2);
	patternStepsLvl2[1][1].setAction(DOWN);
	patternStepsLvl2[1][1].setTimeForStep(1);
	patternStepsLvl2[1][2].setAction(LEFT);
	patternStepsLvl2[1][2].setTimeForStep(2);
	patternStepsLvl2[1][3].setAction(UP);
	patternStepsLvl2[1][3].setTimeForStep(1);

	patternStepsLvl2[2][0].setAction(RIGHT);
	patternStepsLvl2[2][0].setTimeForStep(1);
	patternStepsLvl2[2][1].setAction(UP);
	patternStepsLvl2[2][1].setTimeForStep(1);
	patternStepsLvl2[2][2].setAction(LEFT);
	patternStepsLvl2[2][2].setTimeForStep(1);
	patternStepsLvl2[2][3].setAction(DOWN);
	patternStepsLvl2[2][3].setTimeForStep(1);

	patternStepsLvl2[3][0].setAction(RIGHT);
	patternStepsLvl2[3][0].setTimeForStep(1);
	patternStepsLvl2[3][1].setAction(DOWN);
	patternStepsLvl2[3][1].setTimeForStep(1);
	patternStepsLvl2[3][2].setAction(LEFT);
	patternStepsLvl2[3][2].setTimeForStep(1);
	patternStepsLvl2[3][3].setAction(UP);
	patternStepsLvl2[3][3].setTimeForStep(1);

	patternStepsLvl2[4][0].setAction(RIGHT);
	patternStepsLvl2[4][0].setTimeForStep(2);
	patternStepsLvl2[4][1].setAction(DOWN);
	patternStepsLvl2[4][1].setTimeForStep(1);
	patternStepsLvl2[4][2].setAction(LEFT);
	patternStepsLvl2[4][2].setTimeForStep(2);
	patternStepsLvl2[4][3].setAction(UP);
	patternStepsLvl2[4][3].setTimeForStep(1);

	patternStepsLvl2[5][0].setAction(RIGHT);
	patternStepsLvl2[5][0].setTimeForStep(1);
	patternStepsLvl2[5][1].setAction(RIGHT);
	patternStepsLvl2[5][1].setTimeForStep(1);
	patternStepsLvl2[5][2].setAction(LEFT);
	patternStepsLvl2[5][2].setTimeForStep(1);
	patternStepsLvl2[5][3].setAction(LEFT);
	patternStepsLvl2[5][3].setTimeForStep(1);

	patternStepsLvl2[6][0].setAction(RIGHT);
	patternStepsLvl2[6][0].setTimeForStep(1);
	patternStepsLvl2[6][1].setAction(DOWN);
	patternStepsLvl2[6][1].setTimeForStep(1);
	patternStepsLvl2[6][2].setAction(LEFT);
	patternStepsLvl2[6][2].setTimeForStep(1);
	patternStepsLvl2[6][3].setAction(UP);
	patternStepsLvl2[6][3].setTimeForStep(1);
}