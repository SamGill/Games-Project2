// Programming 2D Games
// Copyright (c) 2011, 2012 by: 
// Charles Kelly
// Collision types demo
// Press '1', '2' or '3' to select collision type for ship.

#include "collisionTypes.h"
#include <sstream>
#include <string>

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
	gamestates = intro;

	timeInState = 0;
	score = 0;
	isMusicPlaying = false;
	isBaseOneDead = false;
	isBaseTwoDead = false;
	havePowerUp = false;
	isLaserPlaying = false;
	isCannonPlaying = false;
	isPowerupPlaying = false;

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

	for(int i = 0; i < LONG_HZ_WALLS; i++)
	{
		if (!wallLgHzScreen[i].initialize(this, 320, 32, 0, &wallLgHzTexture))
			throw(GameError(gameErrorNS::WARNING, "wall long horizontal not initialized"));
	}
	if (!wallLgVtScreen.initialize(this, wallLgVtTexture.getWidth(),wallLgVtTexture.getHeight(),0, &wallLgVtTexture))
		throw(GameError(gameErrorNS::WARNING, "wall long vertical not initialized"));
	for(int i = 0; i < SHORT_HZ_WALLS; i++)
	{
		if (!wallShortHzScreen[i].initialize(this, wallShortHzTexture.getWidth(),wallShortHzTexture.getHeight(),0, &wallShortHzTexture))
			throw(GameError(gameErrorNS::WARNING, "wall short horizontal not initialized"));
	}
	for(int i = 0; i < SHORT_VT_WALLS; i++)
	{
		if (!wallShortVtScreen[i].initialize(this, wallShortVtTexture.getWidth(),wallShortVtTexture.getHeight(),0, &wallShortVtTexture))
			throw(GameError(gameErrorNS::WARNING, "wall short vertical not initialized"));
	}

	//Placement of walls
	wallLgHzScreen[0].setX(wallOneX);
	wallLgHzScreen[0].setY(wallOneY);

#pragma endregion Level One Walls


#pragma region levelOneTextures
#pragma region Level Two Walls

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

	wallLvl2Horizontal[2].setX(GAME_WIDTH/2 + 252/2 - 10);
	wallLvl2Horizontal[2].setY(GAME_HEIGHT/2);


	wallLvl2Vertical[0].setX(GAME_WIDTH/2);
	wallLvl2Vertical[0].setY(0);

	wallLvl2Vertical[1].setX(GAME_WIDTH/5);
	wallLvl2Vertical[1].setY(GAME_HEIGHT - wallLvl2Vertical[1].getHeight());

	wallLvl2Vertical[2].setX(GAME_WIDTH/2 - 10);
	wallLvl2Vertical[2].setY(GAME_HEIGHT/2 + 252/2 + 40);

#pragma endregion

#pragma endregion Level One Walls

#pragma region levelOneTextures

	if (!enemyTankTexture.initialize(graphics, ENEMY_TANK))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if (!tankCrackOneTexture.initialize(graphics, TANK_CRACK_ONE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if (!tankCrackTwoTexture.initialize(graphics, TANK_CRACK_TWO))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));




	if (!tankBodyTexture.initialize(graphics, TANK_BODY))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if (!tankHeadTexture.initialize(graphics, TANK_HEAD))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if (!bulletTexture.initialize(graphics, BULLET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if (!wallTexture.initialize(graphics, WALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if(!powerupTexture.initialize(graphics, POWER_UP))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if(!enemyBaseTexture.initialize(graphics, ENEMY_BASE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing texture"));

	if(!enemyBase.initialize(this, gillNS::WIDTH, gillNS::HEIGHT, 0, &enemyBaseTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing powerup"));

	if (!powerup.initialize(this, murrayNS::WIDTH, murrayNS::HEIGHT, 0, &powerupTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing powerup"));

	if (!powerup.initialize(this, murrayNS::WIDTH, murrayNS::HEIGHT, 0, &powerupTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing powerup"));

	if (!playerTank.initialize(this, playerTankNS::WIDTH, playerTankNS::HEIGHT, 3, &tankBodyTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing body"));

	if (!crackTwo.initialize(this, playerTankNS::WIDTH, playerTankNS::HEIGHT, 0, &tankCrackTwoTexture))
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

	//TRANSITION SCREEN
	if (!transitionTexture.initialize(graphics,TRANSITION))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing transition screen texture"));
	if (!transitionScreen.initialize(graphics, transitionTexture.getWidth(), transitionTexture.getHeight(),0, &transitionTexture))
		throw(GameError(gameErrorNS::WARNING, "Transition not initialized"));
	transitionScreen.setX(0);
	transitionScreen.setY(0);

	//INSTRUCTION SCREEN
	if (!instructionsTexture.initialize(graphics,INSTRUCTIONS))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing instructions screen texture"));
	if (!instructionsScreen.initialize(graphics, instructionsTexture.getWidth(),instructionsTexture.getHeight(),0, &instructionsTexture))
		throw(GameError(gameErrorNS::WARNING, "instructions not initialized"));
	instructionsScreen.setX(0);
	instructionsScreen.setY(0);

	//VICTORY SCREEN
	if (!victoryTexture.initialize(graphics,VICTORY))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing victory screen texture"));
	if (!victoryScreen.initialize(graphics, victoryTexture.getWidth(), victoryTexture.getHeight(),0, &victoryTexture))
		throw(GameError(gameErrorNS::WARNING, "victory not initialized"));
	victoryScreen.setX(0);
	victoryScreen.setY(0);

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

	//SAND BACKGROUND
	if(!sandTexture.initialize(graphics, SAND_BACKGROUND))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sand screen texture"));
	if(!sandScreen.initialize(graphics, sandTexture.getWidth(), sandTexture.getHeight(), 0, &sandTexture))
		throw(GameError(gameErrorNS::WARNING, "Game menu screen not initialized"));
	sandScreen.setX(0);
	sandScreen.setY(0);

	//CHEAT CODE SCREEN
	if(!cheatCodeTexture.initialize(graphics, CHEAT_SCREEN))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cheat code screen texture"));
	if(!cheatCodeScreen.initialize(graphics, cheatCodeTexture.getWidth(), cheatCodeTexture.getHeight(), 0, &cheatCodeTexture))
		throw(GameError(gameErrorNS::WARNING, "Cheat code screen not initialized"));
	cheatCodeScreen.setX(0);
	cheatCodeScreen.setY(0);
#pragma endregion levelOneTextures
	//Placement of walls
#pragma region levelOneWall
	//Long horizontal walls
	wallLgHzScreen[0].setX(wallOneX);
	wallLgHzScreen[0].setY(wallOneY);

	wallLgHzScreen[1].setX(wallNineX);
	wallLgHzScreen[1].setY(wallNineY);

	wallLgHzScreen[2].setX(wallElevenX);
	wallLgHzScreen[2].setY(wallElevenY);

	wallLgHzScreen[3].setX(wallFourX);
	wallLgHzScreen[3].setY(wallFourY);

	wallLgHzScreen[4].setX(wallTwelveX);
	wallLgHzScreen[4].setX(wallTwelveX);

	//Short vertical walls
	wallShortVtScreen[0].setX(wallTwoX);
	wallShortVtScreen[0].setY(wallTwoY);

	wallShortVtScreen[1].setX(wallFiveX);
	wallShortVtScreen[1].setY(wallFiveY);

	wallShortVtScreen[2].setX(wallTenX);
	wallShortVtScreen[2].setY(wallTenY);

	//Short horizontal walls
	wallShortHzScreen[0].setX(wallSixX);
	wallShortHzScreen[0].setY(wallSixY);

	wallShortHzScreen[1].setX(wallSevenX);
	wallShortHzScreen[1].setY(wallSevenY);

	wallShortHzScreen[2].setX(wallThreeX);
	wallShortHzScreen[2].setY(wallThreeY);

	//Long vertical walls
	wallLgVtScreen.setX(0);
	wallLgVtScreen.setY(280);

#pragma endregion levelOneWall
	//Powerup placement
	powerup.setX(1100);
	powerup.setY(50);

	powerup.setCollisionType(entityNS::BOX);
	powerup.setEdge(POWERUP_RECT);

	//Base placement
	enemyBase.setX(1040);
	enemyBase.setY(520);
	enemyBase.setCollisionType(entityNS::BOX);
	enemyBase.setEdge(ENEMY_BASE_RECT);


	//Wall long horizontal collision box
	for(int i = 0; i < LONG_HZ_WALLS; i++)
	{
		wallLgHzScreen[i].setCollisionType(entityNS::BOX);
		wallLgHzScreen[i].setEdge(WALL_LONG_HZ_RECT);
	}

	//Wall short vertical collision box
	for (int i = 0; i < SHORT_VT_WALLS; i++)
	{
		wallShortVtScreen[i].setCollisionType(entityNS::BOX);
		wallShortVtScreen[i].setEdge(WALL_SHORT_VT_RECT);
	}

	//Wall short horizontal collision box
	for (int i = 0; i < SHORT_HZ_WALLS; i++)
	{
		wallShortHzScreen[i].setCollisionType(entityNS::BOX);
		wallShortHzScreen[i].setEdge(WALL_SHORT_HZ_RECT);
	}

	//Wall long vertical collision box
	wallLgVtScreen.setCollisionType(entityNS::BOX);
	wallLgVtScreen.setEdge(WALL_LONG_VT_RECT);

	wall.setScale(.5f);
	wall.setCollisionType(entityNS::BOX);

	RECT collision  = {-45,-10,45,10};
	wall.setEdge(WALL_RECTANGLE);
	wall.setX(400);
	wall.setY(400);

	for (int i = 0; i < MAX_ENEMY_TANKS; i++)
	{
		enemyTanks[i].setScale(.15f);
		enemyTanks[i].setEdge(TANK_RECTANGLE);
		enemyTanks[i].setPosition(VECTOR2(-1,-1));
	}

#pragma region stateTwo information
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
#pragma endregion

	//Enemy tank placement
	enemyTanks[0].setPositionX(levelOneTankOneX);
	enemyTanks[0].setPositionY(levelOneTankOneY);
	enemyTanks[1].setPositionX(levelOneTankTwoX);
	enemyTanks[1].setPositionY(levelOneTankTwoY);
	enemyTanks[2].setPositionX(levelOneTankThreeX);
	enemyTanks[2].setPositionY(levelOneTankThreeY);
	enemyTanks[3].setPositionX(levelOneTankFourX);
	enemyTanks[3].setPositionY(levelOneTankFourY);
	enemyTanks[4].setPositionX(levelOneTankFiveX);
	enemyTanks[4].setPositionY(levelOneTankFiveY);
	enemyTanks[5].setPositionX(levelOneTankSixX);
	enemyTanks[5].setPositionY(levelOneTankSixY);
	enemyTanks[6].setPositionX(levelOneTankSevenX);
	enemyTanks[6].setPositionY(levelOneTankSevenY);


	playerTank.setCurrentFrame(0);
	playerTank.setScale(.15f);

	playerTank.setX(levelOnePlayerX);
	playerTank.setY(levelOnePlayerY);

	if (!playerTank.initializeHead(this, tankHeadNS::WIDTH,tankHeadNS::HEIGHT,0, &tankHeadTexture, &bulletTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing head"));


	playerTank.setCollisionType(entityNS::ROTATED_BOX);
	playerTank.setEdge(TANK_RECTANGLE);

	for (int i = 0; i < MAX_ENEMY_TANKS; i++)
	{
		enemyTanks[i].setCollisionType(entityNS::ROTATED_BOX);
		enemyTanks[i].setEdge(TANK_RECTANGLE);
	}

	scoreFont = new TextDX();
	finalScoreFont = new TextDX();

	//Initialize the game text
	if(scoreFont->initialize(graphics, 24, true, false, "Arial") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing output font"));

	if(finalScoreFont->initialize(graphics, 48, true, false, "Bauhaus 93") == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing output font"));

	finalScoreFont->setFontColor(graphicsNS::RED);
	scoreFont->setFontColor(graphicsNS::RED);

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


#pragma region patternStepInitialize
	patternStepIndex = 0;
	for (int i = 0; i < maxPatternSteps; i++)
	{
		patternSteps[i].initialize(&enemyTanks[0]);
		patternSteps[i].setActive();
	}

	patternStepIndex2 = 0;
	for (int i = 0; i < maxPatternSteps; i++)
	{
		patternSteps2[i].initialize(&enemyTanks[1]);
		patternSteps2[i].setActive();
	}

	patternStepIndex3 = 0;
	for (int i = 0; i < maxPatternSteps; i++)
	{
		patternSteps3[i].initialize(&enemyTanks[2]);
		patternSteps3[i].setActive();
	}

	patternStepIndex4 = 0;
	for (int i = 0; i < maxPatternSteps; i++)
	{
		patternSteps4[i].initialize(&enemyTanks[3]);
		patternSteps4[i].setActive();
	}

	patternStepIndex5 = 0;
	for (int i = 0; i < maxPatternSteps; i++)
	{
		patternSteps5[i].initialize(&enemyTanks[4]);
		patternSteps5[i].setActive();
	}

	patternStepIndex6 = 0;
	for (int i = 0; i < maxPatternSteps; i++)
	{
		patternSteps6[i].initialize(&enemyTanks[5]);
		patternSteps6[i].setActive();
	}

	patternStepIndex7 = 0;
	for (int i = 0; i < maxPatternSteps; i++)
	{
		patternSteps7[i].initialize(&enemyTanks[6]);
		patternSteps7[i].setActive();
	}

#pragma endregion patternStepInitialize
	enemyUpDown();
	enemyUpDown2();
	enemyLeftRight();
	enemyLeftRight2();
	enemyLeftRight3();
	enemyLeftRight4();
	enemyLeftRight5();


#pragma region patternStepInitialize
	patternStepIndex = 0;
	for (int i = 0; i < maxPatternSteps; i++)
	{
		patternSteps[i].initialize(&enemyTanks[0]);
		patternSteps[i].setActive();
	}

	patternStepIndex2 = 0;
	for (int i = 0; i < maxPatternSteps; i++)
	{
		patternSteps2[i].initialize(&enemyTanks[1]);
		patternSteps2[i].setActive();
	}

	patternStepIndex3 = 0;
	for (int i = 0; i < maxPatternSteps; i++)
	{
		patternSteps3[i].initialize(&enemyTanks[2]);
		patternSteps3[i].setActive();
	}

	patternStepIndex4 = 0;
	for (int i = 0; i < maxPatternSteps; i++)
	{
		patternSteps4[i].initialize(&enemyTanks[3]);
		patternSteps4[i].setActive();
	}

	patternStepIndex5 = 0;
	for (int i = 0; i < maxPatternSteps; i++)
	{
		patternSteps5[i].initialize(&enemyTanks[4]);
		patternSteps5[i].setActive();
	}

	patternStepIndex6 = 0;
	for (int i = 0; i < maxPatternSteps; i++)
	{
		patternSteps6[i].initialize(&enemyTanks[5]);
		patternSteps6[i].setActive();
	}

	patternStepIndex7 = 0;
	for (int i = 0; i < maxPatternSteps; i++)
	{
		patternSteps7[i].initialize(&enemyTanks[6]);
		patternSteps7[i].setActive();
	}

#pragma endregion patternStepInitialize
	enemyUpDown();
	enemyUpDown2();
	enemyLeftRight();
	enemyLeftRight2();
	enemyLeftRight3();
	enemyLeftRight4();
	enemyLeftRight5();
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
			//gamestates = level_two;

			timeInState = 0;
		}
		//If "C" is pressed, go to cheat code screen
		if(input->wasKeyPressed(0x43))
		{
			gamestates = cheatCodes;
			timeInState = 0;
		}

		if(input->wasKeyPressed(0x49))
		{
			gamestates = instructions;
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
			playerTank.setHealth(10000000.0f);
		}
		//If "W" was pressed, give all weapons
		if(input->wasKeyPressed(0x57))
		{
			havePowerUp = true;
		}
		//If "2" was pressed, jump to level 2
		if(input->wasKeyPressed(0x32))
		{
			//Jump to level 2
			gamestates = level_two;
			timeInState = 0;
		}
		//If "ESC" was pressed, go back to main menu
		if(input->wasKeyPressed(ESC_KEY))
		{
			gamestates = gameMenu;
			timeInState = 0;
		}
	}

	//Moves to game over screen, but only for testing
	if(gamestates == level_one)
	{
		if(isBaseOneDead)
		{
			gamestates = levelTransition;
			timeInState = 0;
		}

		//Just for testing
		if(input->wasKeyPressed(0x32))
		{
			//Jump to level 2
			gamestates = victory;
		}

		timeInState = 0;
	}

	if(gamestates == levelTransition && timeInState > 3)
	{
		initializeLvlTwoPatterns();

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

		for (int i = 0; i < MAX_ENEMY_TANKS; i++)
		{
			enemyTanks[i].setHealth(100);
			enemyTanks[i].setVisible();
		}

		enemyBase.setHealth(100);
		enemyBase.setY(enemyBase.getY() + enemyBase.getHeight() * enemyBase.getScale());

		playerTank.setX(levelOnePlayerX);
		playerTank.setY(levelOnePlayerY);
		playerTank.setRadians(PI/4);

		gamestates = level_two;
		timeInState = 0;
	}

	if(gamestates == instructions)
	{
		if(input->wasKeyPressed(ESC_KEY))
		{
			gamestates = gameMenu;
			timeInState = 0;
		}
	}

	if(gamestates == level_two)
	{
		if(isBaseTwoDead)
		{
			gamestates = victory;
			timeInState = 0;
		}
	}

	if(gamestates == victory)
	{
		//If "Y" pressed
		if(input->wasKeyPressed(0x59))
		{
			gamestates = intro;
			timeInState = 0;
		}
		if(input->wasKeyPressed(0x4E))
		{
			PostQuitMessage(0);
		}
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
	case instructions:
		break;
	case levelTransition:
		break;
	case level_one:
		if(!isMusicPlaying)
		{
			audio->playCue(MAIN_MUSIC);
			isMusicPlaying = true;
		}

		playerTank.setVelocity(VECTOR2(0,0));
		if(input->isKeyDown(TANK_UP_KEY))
			playerTank.forward();
		if(input->isKeyDown(TANK_DOWN_KEY))
			playerTank.reverse();
		playerTank.rotate(playerTankNS::NONE);
		if (input->isKeyDown(TANK_LEFT_KEY))   
			playerTank.rotate(playerTankNS::LEFT);
		if (input->isKeyDown(TANK_RIGHT_KEY))
			playerTank.rotate(playerTankNS::RIGHT);

		if (input->getMouseLButton())
		{
			if(havePowerUp)
			{
				timeInState = 0;
				audio->playCue(LASER);
				isLaserPlaying = true;
			}
			else if(!havePowerUp)
			{
				timeInState = 0;
				audio->playCue(CANNON);
				isCannonPlaying = true;
			}

			playerTank.fireBullet();
		


		}
		
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
		{
			playerTank.forward();
		}
		if(input->isKeyDown(TANK_DOWN_KEY))
		{
			playerTank.reverse();
		}
		playerTank.rotate(playerTankNS::NONE);
		if (input->isKeyDown(TANK_LEFT_KEY))
		{
			playerTank.rotate(playerTankNS::LEFT);
		}
		if (input->isKeyDown(TANK_RIGHT_KEY))
		{
			playerTank.rotate(playerTankNS::RIGHT);
		}

		if (input->getMouseLButton())
			playerTank.fireBullet();
		playerTank.update(frameTime);
		for (int i = 0; i < MAX_ENEMY_TANKS; i++)
			enemyTanks[i].update(frameTime);

		if(playerTank.getHealth() <= 80.0f && playerTank.getHealth() > 40.0f)
			playerTank.setCurrentFrame(1);
		else if(playerTank.getHealth() <= 40.0f && playerTank.getHealth() > 0.0f)
			playerTank.setCurrentFrame(2);
		else
			playerTank.setCurrentFrame(0);

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
	enemyTanks[0].ai(frameTime, playerTank);
	float distance =  D3DXVec2Length(&(enemyTanks[0].getCenterPoint()-playerTank.getCenterPoint()));
	float distance2 = D3DXVec2Length(&(enemyTanks[1].getCenterPoint()-playerTank.getCenterPoint()));
	float distance3 = D3DXVec2Length(&(enemyTanks[2].getCenterPoint()-playerTank.getCenterPoint()));
	float distance4 = D3DXVec2Length(&(enemyTanks[3].getCenterPoint()-playerTank.getCenterPoint()));
	float distance5 = D3DXVec2Length(&(enemyTanks[4].getCenterPoint()-playerTank.getCenterPoint()));
	float distance6 = D3DXVec2Length(&(enemyTanks[5].getCenterPoint()-playerTank.getCenterPoint()));
	float distance7 = D3DXVec2Length(&(enemyTanks[6].getCenterPoint()-playerTank.getCenterPoint()));

#pragma region distance
	if(distance < 100.0f)
	{
		enemyTanks[0].ai(frameTime, playerTank);
		patternStepIndex = 4;
		patternSteps[4].initialize(&enemyTanks[0]);
		patternSteps[4].setActive();
	}
	else if(patternStepIndex == maxPatternSteps - 1)
	{
		enemyTanks[0].ai(frameTime, playerTank);
		for (int i = 0; i < maxPatternSteps - 1; i++)
		{
			patternSteps[i].initialize(&enemyTanks[0]);
			patternSteps[i].setActive();
		}
		patternStepIndex = 0;
	}
	if(distance2 < 100.0f)
	{
		enemyTanks[1].ai(frameTime, playerTank);
		patternStepIndex2 = 4;
		patternSteps2[4].initialize(&enemyTanks[1]);
		patternSteps2[4].setActive();
	}
	else if(patternStepIndex2 == maxPatternSteps - 1)
	{
		enemyTanks[1].ai(frameTime, playerTank);
		for (int i = 0; i < maxPatternSteps - 1; i++)
		{
			patternSteps2[i].initialize(&enemyTanks[1]);
			patternSteps2[i].setActive();
		}
		patternStepIndex2 = 0;
	}
	if(distance3 < 100.0f)
	{
		enemyTanks[2].ai(frameTime, playerTank);
		patternStepIndex3 = 4;
		patternSteps3[4].initialize(&enemyTanks[2]);
		patternSteps3[4].setActive();
	}
	else if(patternStepIndex3 == maxPatternSteps - 1)
	{
		enemyTanks[2].ai(frameTime, playerTank);
		for (int i = 0; i < maxPatternSteps - 1; i++)
		{
			patternSteps3[i].initialize(&enemyTanks[2]);
			patternSteps3[i].setActive();
		}
		patternStepIndex3 = 0;
	}
	if(distance4 < 100.0f)
	{
		enemyTanks[3].ai(frameTime, playerTank);
		patternStepIndex4 = 4;
		patternSteps4[4].initialize(&enemyTanks[3]);
		patternSteps4[4].setActive();
	}
	else if(patternStepIndex4 == maxPatternSteps - 1)
	{
		enemyTanks[3].ai(frameTime, playerTank);
		for (int i = 0; i < maxPatternSteps - 1; i++)
		{
			patternSteps4[i].initialize(&enemyTanks[3]);
			patternSteps4[i].setActive();
		}
		patternStepIndex4 = 0;
	}
	if(distance5 < 100.0f)
	{
		enemyTanks[4].ai(frameTime, playerTank);
		patternStepIndex5 = 4;
		patternSteps5[4].initialize(&enemyTanks[4]);
		patternSteps5[4].setActive();
	}
	else if(patternStepIndex5 == maxPatternSteps - 1)
	{
		enemyTanks[4].ai(frameTime, playerTank);
		for (int i = 0; i < maxPatternSteps - 1; i++)
		{
			patternSteps5[i].initialize(&enemyTanks[4]);
			patternSteps5[i].setActive();
		}
		patternStepIndex5 = 0;
	}
	if(distance6 < 100.0f)
	{
		enemyTanks[5].ai(frameTime, playerTank);
		patternStepIndex6 = 4;
		patternSteps6[4].initialize(&enemyTanks[5]);
		patternSteps6[4].setActive();
	}
	else if(patternStepIndex6 == maxPatternSteps - 1)
	{
		enemyTanks[5].ai(frameTime, playerTank);
		for (int i = 0; i < maxPatternSteps - 1; i++)
		{
			patternSteps6[i].initialize(&enemyTanks[5]);
			patternSteps6[i].setActive();
		}
		patternStepIndex6 = 0;
	}

	if(distance7 < 100.0f)
	{
		enemyTanks[6].ai(frameTime, playerTank);
		patternStepIndex7 = 4;
		patternSteps7[4].initialize(&enemyTanks[6]);
		patternSteps7[4].setActive();
	}
	else if(patternStepIndex7 == maxPatternSteps - 1)
	{
		enemyTanks[6].ai(frameTime, playerTank);
		for (int i = 0; i < maxPatternSteps - 1; i++)
		{
			patternSteps7[i].initialize(&enemyTanks[6]);
			patternSteps7[i].setActive();
		}
		patternStepIndex7 = 0;
	}
#pragma endregion distance

#pragma region updatePattern
	if (patternSteps[patternStepIndex].isFinished())
		patternStepIndex++;
	patternSteps[patternStepIndex].update(frameTime);

	if (patternSteps2[patternStepIndex2].isFinished())
		patternStepIndex2++;
	patternSteps2[patternStepIndex2].update(frameTime);

	if (patternSteps3[patternStepIndex3].isFinished())
		patternStepIndex3++;
	patternSteps3[patternStepIndex3].update(frameTime);

	if (patternSteps4[patternStepIndex4].isFinished())
		patternStepIndex4++;
	patternSteps4[patternStepIndex4].update(frameTime);

	if (patternSteps5[patternStepIndex5].isFinished())
		patternStepIndex5++;
	patternSteps5[patternStepIndex5].update(frameTime);

	if (patternSteps6[patternStepIndex6].isFinished())
		patternStepIndex6++;
	patternSteps6[patternStepIndex6].update(frameTime);

	if (patternSteps7[patternStepIndex7].isFinished())
		patternStepIndex7++;
	patternSteps7[patternStepIndex7].update(frameTime);
#pragma endregion updatePattern
	switch(gamestates)
	{
	case level_one:


#pragma region distance
		if(distance < 100.0f)
		{
			enemyTanks[0].ai(frameTime, playerTank);
			patternStepIndex = 4;
			patternSteps[4].initialize(&enemyTanks[0]);
			patternSteps[4].setActive();
		}
		else if(patternStepIndex == maxPatternSteps - 1)
		{
			enemyTanks[0].ai(frameTime, playerTank);
			for (int i = 0; i < maxPatternSteps - 1; i++)
			{
				patternSteps[i].initialize(&enemyTanks[0]);
				patternSteps[i].setActive();
			}
			patternStepIndex = 0;
		}
		if(distance2 < 100.0f)
		{
			enemyTanks[1].ai(frameTime, playerTank);
			patternStepIndex2 = 4;
			patternSteps2[4].initialize(&enemyTanks[1]);
			patternSteps2[4].setActive();
		}
		else if(patternStepIndex2 == maxPatternSteps - 1)
		{
			enemyTanks[1].ai(frameTime, playerTank);
			for (int i = 0; i < maxPatternSteps - 1; i++)
			{
				patternSteps2[i].initialize(&enemyTanks[1]);
				patternSteps2[i].setActive();
			}
			patternStepIndex2 = 0;
		}
		if(distance3 < 100.0f)
		{
			enemyTanks[2].ai(frameTime, playerTank);
			patternStepIndex3 = 4;
			patternSteps3[4].initialize(&enemyTanks[2]);
			patternSteps3[4].setActive();
		}
		else if(patternStepIndex3 == maxPatternSteps - 1)
		{
			enemyTanks[2].ai(frameTime, playerTank);
			for (int i = 0; i < maxPatternSteps - 1; i++)
			{
				patternSteps3[i].initialize(&enemyTanks[2]);
				patternSteps3[i].setActive();
			}
			patternStepIndex3 = 0;
		}
		if(distance4 < 100.0f)
		{
			enemyTanks[3].ai(frameTime, playerTank);
			patternStepIndex4 = 4;
			patternSteps4[4].initialize(&enemyTanks[3]);
			patternSteps4[4].setActive();
		}
		else if(patternStepIndex4 == maxPatternSteps - 1)
		{
			enemyTanks[3].ai(frameTime, playerTank);
			for (int i = 0; i < maxPatternSteps - 1; i++)
			{
				patternSteps4[i].initialize(&enemyTanks[3]);
				patternSteps4[i].setActive();
			}
			patternStepIndex4 = 0;
		}
		if(distance5 < 100.0f)
		{
			enemyTanks[4].ai(frameTime, playerTank);
			patternStepIndex5 = 4;
			patternSteps5[4].initialize(&enemyTanks[4]);
			patternSteps5[4].setActive();
		}
		else if(patternStepIndex5 == maxPatternSteps - 1)
		{
			enemyTanks[4].ai(frameTime, playerTank);
			for (int i = 0; i < maxPatternSteps - 1; i++)
			{
				patternSteps5[i].initialize(&enemyTanks[4]);
				patternSteps5[i].setActive();
			}
			patternStepIndex5 = 0;
		}
		if(distance6 < 100.0f)
		{
			enemyTanks[5].ai(frameTime, playerTank);
			patternStepIndex6 = 4;
			patternSteps6[4].initialize(&enemyTanks[5]);
			patternSteps6[4].setActive();
		}
		else if(patternStepIndex6 == maxPatternSteps - 1)
		{
			enemyTanks[5].ai(frameTime, playerTank);
			for (int i = 0; i < maxPatternSteps - 1; i++)
			{
				patternSteps6[i].initialize(&enemyTanks[5]);
				patternSteps6[i].setActive();
			}
			patternStepIndex6 = 0;
		}

		if(distance7 < 100.0f)
		{
			enemyTanks[6].ai(frameTime, playerTank);
			patternStepIndex7 = 4;
			patternSteps7[4].initialize(&enemyTanks[6]);
			patternSteps7[4].setActive();
		}
		else if(patternStepIndex7 == maxPatternSteps - 1)
		{
			enemyTanks[6].ai(frameTime, playerTank);
			for (int i = 0; i < maxPatternSteps - 1; i++)
			{
				patternSteps7[i].initialize(&enemyTanks[6]);
				patternSteps7[i].setActive();
			}
			patternStepIndex7 = 0;
		}
#pragma endregion distance

#pragma region updatePattern
		if (patternSteps[patternStepIndex].isFinished())
			patternStepIndex++;
		patternSteps[patternStepIndex].update(frameTime);

		if (patternSteps2[patternStepIndex2].isFinished())
			patternStepIndex2++;
		patternSteps2[patternStepIndex2].update(frameTime);

		if (patternSteps3[patternStepIndex3].isFinished())
			patternStepIndex3++;
		patternSteps3[patternStepIndex3].update(frameTime);

		if (patternSteps4[patternStepIndex4].isFinished())
			patternStepIndex4++;
		patternSteps4[patternStepIndex4].update(frameTime);

		if (patternSteps5[patternStepIndex5].isFinished())
			patternStepIndex5++;
		patternSteps5[patternStepIndex5].update(frameTime);

		if (patternSteps6[patternStepIndex6].isFinished())
			patternStepIndex6++;
		patternSteps6[patternStepIndex6].update(frameTime);

		if (patternSteps7[patternStepIndex7].isFinished())
			patternStepIndex7++;
		patternSteps7[patternStepIndex7].update(frameTime);
#pragma endregion updatePattern
		break;
	case level_two:
		for (int i = 0; i < MAX_ENEMY_TANKS; i++)
		{
			enemyTanks[i].ai(frameTime, playerTank);
			performEnemyTankPatternStep(i);
		}
	}
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

	switch (gamestates)
	{
#pragma region level1
	case level_one:
		if(playerTank.collidesWith(powerup, collisionVector))
		{
			powerup.setVisible(false);
			havePowerUp = true;
		}

		if(havePowerUp)
		{
			//Change bullet
			for (int i = 0; i < MAX_PLAYER_SHOTS; i++)
			{
				playerTank.head.bullet[i].setCurrentFrame(1);
				playerTank.head.bullet[i].setScale(.5f);
			}
		}


		for (int i = 0; i < MAX_ENEMY_TANKS; i++)
		{

			for (int j = 0; j < NUM_ENEMY_BULLETS; j++)
			{
				Bullet* eBullets = enemyTanks[i].getBullets();
				if (eBullets[j].collidesWith(playerTank, collisionVector) && eBullets[j].getVisible())
				{
					playerTank.setHealth(playerTank.getHealth() - 20.0f);
					if (playerTank.getHealth() == 60.0f)
						playerTank.setCurrentFrame(1);
					else if (playerTank.getHealth() == 20)
						playerTank.setCurrentFrame(2);
					else if (playerTank.getHealth() == 0)
						gamestates = gameover;

					eBullets[j].setVisible(false);

					gameStatesUpdate();
				}

			}

			if (playerTank.collidesWith(enemyTanks[i], collisionVector))
			{
				playerTank.setVelocity(VECTOR2(-collisionVector));
				enemyTanks[i].setVelocity(VECTOR2(collisionVector));
				playerTank.setCollision(true);
			}

			for (int j = 0; j < LONG_HZ_WALLS; j++)
			{
				if(enemyTanks[i].collidesWith(wallLgHzScreen[j], collisionVector))
				{
					enemyTanks[i].setCollision(true);
					enemyTanks[i].bounce(collisionVector, wallLgHzScreen[j]);
				}
				Bullet* bullets = enemyTanks[i].getBullets();
				for (int z = 0; z < NUM_ENEMY_BULLETS; z++)
				{
					if (bullets[z].collidesWith(wallLgHzScreen[j], collisionVector))
						bullets[z].setVisible(false);
				}
			}

			for (int j = 0; j < LONG_VT_WALLS; j++)
			{
				Bullet* bullets = enemyTanks[i].getBullets();
				for (int z = 0; z < NUM_ENEMY_BULLETS; z++)
				{
					if (bullets[z].collidesWith(wallLgVtScreen, collisionVector))
						bullets[z].setVisible(false);
				}
			}

			for (int j = 0; j < SHORT_HZ_WALLS; j++)
			{
				Bullet* bullets = enemyTanks[i].getBullets();
				for (int z = 0; z < NUM_ENEMY_BULLETS; z++)
				{
					if (bullets[z].collidesWith(wallShortHzScreen[j], collisionVector))
						bullets[z].setVisible(false);
				}
			}

			for (int j = 0; j < SHORT_VT_WALLS; j++)
			{
				Bullet* bullets = enemyTanks[i].getBullets();
				for (int z = 0; z < NUM_ENEMY_BULLETS; z++)
				{
					if (bullets[z].collidesWith(wallShortVtScreen[j], collisionVector))
						bullets[z].setVisible(false);
				}
			}

		}

#pragma region bulletWall

              for (int i = 0; i < MAX_PLAYER_SHOTS; i++)
              {
                     //Long Hz Collision
                     for (int j = 0; j < LONG_HZ_WALLS; j++)
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

                     //Short Hz Collision
                     for (int j = 0; j < SHORT_HZ_WALLS; j++)
                     {
                           if (bullets[i].collidesWith(wallShortHzScreen[j], collisionVector))
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

                     //Short Vt Collision
                     for (int j = 0; j < SHORT_VT_WALLS; j++)
                     {
                           if (bullets[i].collidesWith(wallShortVtScreen[j], collisionVector))
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

                     //Long Vt Collision
                     for (int j = 0; j < LONG_VT_WALLS; j++)
                     {
                           if (bullets[i].collidesWith(wallLgVtScreen, collisionVector))
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
							if (enemyTanks[j].getVisible() && bullets[i].collidesWith(enemyTanks[j], collisionVector) && bullets[i].getVisible())
							{
								float currentHealth = enemyTanks[j].getHealth();
								if(!havePowerUp)
									enemyTanks[j].setHealth(enemyTanks[j].getHealth() - 20.0f);
								else
									enemyTanks[j].setHealth(enemyTanks[j].getHealth() - 100.0f);
								if (enemyTanks[j].getHealth() <= 0.0f)
								{
										enemyTanks[j].setInvisible();
										score += 100;
										audio->playCue(EXPLOSION);
								}
								bullets[i].setVisible(false);
							}
                     }

                     if (bullets[i].collidesWith(enemyBase, collisionVector) && bullets[i].getVisible())
                     {
                           float currentHealth = enemyBase.getHealth();
						   if(!havePowerUp)
								enemyBase.setHealth(enemyBase.getHealth() - 10.0f);
						   else
							   enemyBase.setHealth(enemyBase.getHealth() - 20.0f);
                           if (enemyBase.getHealth() <= 0.0f)
                           {
                                  //enemyBase.setInvisible();
                                  score += 1000;
								  isBaseOneDead = true;
								  audio->playCue(EXPLOSION);
								  gamestates = levelTransition;
                           }
                           bullets[i].setVisible(false);
                     }

              }

		for (int i = 0; i < MAX_PLAYER_SHOTS; i++)
		{
			//Long Hz Collision
			for (int j = 0; j < LONG_HZ_WALLS; j++)
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

			//Short Hz Collision
			for (int j = 0; j < SHORT_HZ_WALLS; j++)
			{
				if (bullets[i].collidesWith(wallShortHzScreen[j], collisionVector))
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

			//Short Vt Collision
			for (int j = 0; j < SHORT_VT_WALLS; j++)
			{
				if (bullets[i].collidesWith(wallShortVtScreen[j], collisionVector))
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

			//Long Vt Collision
			for (int j = 0; j < LONG_VT_WALLS; j++)
			{
				if (bullets[i].collidesWith(wallLgVtScreen, collisionVector))
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
				if (enemyTanks[j].getVisible() && bullets[i].collidesWith(enemyTanks[j], collisionVector) && bullets[i].getVisible())
				{
					float currentHealth = enemyTanks[j].getHealth();
					if(!havePowerUp)
						enemyTanks[j].setHealth(enemyTanks[j].getHealth() - 20.0f);
					else
						enemyTanks[j].setHealth(enemyTanks[j].getHealth() - 100.0f);
					if (enemyTanks[j].getHealth() <= 0.0f)
					{
						enemyTanks[j].setInvisible();
						score += 100;
					}
					bullets[i].setVisible(false);
				}
			}

			if (bullets[i].collidesWith(enemyBase, collisionVector) && bullets[i].getVisible())
			{
				float currentHealth = enemyBase.getHealth();
				if(!havePowerUp)
					enemyBase.setHealth(enemyBase.getHealth() - 10.0f);
				else
					enemyBase.setHealth(enemyBase.getHealth() - 20.0f);
				if (enemyBase.getHealth() <= 0.0f)
				{
					//enemyBase.setInvisible();
					score += 1000;
					isBaseOneDead = true;
					gamestates = levelTransition;
				}
				bullets[i].setVisible(false);
			}

		}

#pragma endregion bulletWall

#pragma region playerWall

		for(int i = 0; i < LONG_HZ_WALLS; i++)
		{
			if(playerTank.collidesWith(wallLgHzScreen[i], collisionVector))
			{
				playerTank.setCollision(true);
				playerTank.bounce(collisionVector, wallLgHzScreen[i]);
			}
		}

		for (int i = 0; i < SHORT_VT_WALLS; i++)
		{
			if(playerTank.collidesWith(wallShortVtScreen[i], collisionVector))
			{
				playerTank.setCollision(true);
				playerTank.bounce(collisionVector, wallShortVtScreen[i]);
			}
		}

		for (int i = 0; i < SHORT_HZ_WALLS; i++)
		{
			if (playerTank.collidesWith(wallShortHzScreen[i], collisionVector))
			{
				playerTank.setCollision(true);
				playerTank.bounce(collisionVector, wallShortHzScreen[i]);
			}
		}

		if (playerTank.collidesWith(wallLgVtScreen, collisionVector))
		{
			playerTank.setCollision(true);
			playerTank.bounce(collisionVector, wallLgVtScreen);
		}
		break;
#pragma endregion level1
#pragma region level2
	case level_two:

		if (playerTank.collidesWith(wallLgHzScreen[0], collisionVector))
		{
			playerTank.setCollision(true);
			playerTank.bounce(collisionVector, wallLgHzScreen[0]);
		}

		for (int i = 0; i < MAX_ENEMY_TANKS; i++)
		{
			Bullet* eBullets = enemyTanks[i].getBullets();
			for (int z = 0; z < NUM_ENEMY_BULLETS; z++)
			{
				if (eBullets[z].collidesWith(wallLgHzScreen[0], collisionVector))
					eBullets[z].setVisible(false);


				if (eBullets[z].collidesWith(playerTank, collisionVector) && eBullets[z].getVisible())
				{
					playerTank.setHealth(playerTank.getHealth() - 20.0f);
					if (playerTank.getHealth() == 60.0f)
						playerTank.setCurrentFrame(1);
					else if (playerTank.getHealth() == 20)
						playerTank.setCurrentFrame(2);
					else if (playerTank.getHealth() == 0)
						gamestates = gameover;

					eBullets[z].setVisible(false);

					gameStatesUpdate();
				}
			}
		}


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

				Bullet* eBullets = enemyTanks[j].getBullets();
				for (int z = 0; z < NUM_ENEMY_BULLETS; z++)
				{
					if (eBullets[z].collidesWith(wallLvl2Horizontal[i], collisionVector))
						eBullets[z].setVisible(false);
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

				Bullet* eBullets = enemyTanks[j].getBullets();
				for (int z = 0; z < NUM_ENEMY_BULLETS; z++)
				{
					if (eBullets[z].collidesWith(wallLvl2Vertical[i], collisionVector))
						eBullets[z].setVisible(false);
				}
			}
		}


		//next check for all bullet collisoins
		for (int i = 0; i < MAX_PLAYER_SHOTS; i++)
		{

			for (int j = 0; j < MAX_ENEMY_TANKS; j++)
			{
				if (bullets[i].collidesWith(enemyTanks[j], collisionVector) && bullets[i].getVisible())
				{
					enemyTanks[j].setHealth(enemyTanks[j].getHealth() - 100.0/3);

					if (enemyTanks[j].getHealth() <= 0)
					{
						enemyTanks[j].setInvisible();
						score += 150;
					}

					bullets[i].setVisible(false);
				}

			}

			if (bullets[i].collidesWith(enemyBase, collisionVector) && bullets[i].getVisible())
			{
				float currentHealth = enemyBase.getHealth();
				if(!havePowerUp)
					enemyBase.setHealth(enemyBase.getHealth() - 10.0f);
				else
					enemyBase.setHealth(enemyBase.getHealth() - 20.0f);
				if (enemyBase.getHealth() <= 0.0f)
				{
					//enemyBase.setInvisible();
					score += 2000;
					isBaseOneDead = true;
					gamestates = victory;
				}
				bullets[i].setVisible(false);
			}


			if (bullets[i].collidesWith(wallLgHzScreen[0], collisionVector))
			{
				if (bullets[i].getCollision() == false)
				{
					bullets[i].reflectVelocity(collisionVector);
					bullets[i].setCollision(true);
				}
				continue;                  
			}


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
#pragma endregion level2


#pragma endregion playerWall
}

//=============================================================================
// Render game items
//=============================================================================
void CollisionTypes::render()
{
	//Score display
	std::stringstream scoreDisplay;
	scoreDisplay << "Score: ";
	scoreDisplay << score;

	//Final score display
	std::stringstream finalScoreDisplay;
	finalScoreDisplay << "Final score: ";
	finalScoreDisplay << score;

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
	case instructions:
		instructionsScreen.draw();
		break;
	case levelTransition:
		transitionScreen.draw();
		break;
	case gameMenu:
		gameMenuScreen.draw();
		break;
	case level_one:
		sandScreen.draw();
		playerTank.draw();
		for (int i = 0; i < LONG_HZ_WALLS; i++)
		{
			wallLgHzScreen[i].draw();
		}
		for (int i = 0; i < SHORT_VT_WALLS; i++)
		{
			wallShortVtScreen[i].draw();
		}
		for (int i = 0; i < SHORT_HZ_WALLS; i++)
		{
			wallShortHzScreen[i].draw();
		}
		powerup.draw();
		enemyBase.draw();
		wallLgVtScreen.draw();
		for (int i = 0; i < MAX_ENEMY_TANKS; i++)
			enemyTanks[i].draw();
		playerTank.draw();

		scoreFont->print(scoreDisplay.str(), GAME_WIDTH - 150, 20); //Displays score

		scoreFont->print(scoreDisplay.str(), GAME_WIDTH - 150, 20); //Displays score
		break;
	case level_two:
		sandScreen.draw();
		playerTank.draw();
		wallLgHzScreen[0].draw();
		for (int i = 0; i < NUM_LVL_TWO_HZ_WALL; i++)
			wallLvl2Horizontal[i].draw();
		for (int i = 0; i < NUM_LVL_TWO_VT_WALL; i++)
			wallLvl2Vertical[i].draw();

		for (int i = 0; i < MAX_ENEMY_TANKS; i++)
			enemyTanks[i].draw();
		enemyBase.draw();
		scoreFont->print(scoreDisplay.str(), GAME_WIDTH - 150, 20); //Displays score

		scoreFont->print(scoreDisplay.str(), GAME_WIDTH - 150, 20); //Displays score
		break;
	case victory:
		victoryScreen.draw();
		finalScoreFont->print(finalScoreDisplay.str(), GAME_WIDTH/2 - 200, GAME_HEIGHT/2 - 200);
		break;
	case gameover:
		gameOverScreen.draw();
		break;
	default:
		break;
	}
	graphics->spriteEnd();                  // end drawing sprites
}

//Enemy pattern functions
void CollisionTypes::enemyUpDown()
{
	patternSteps[0].setAction(RIGHT);
	patternSteps[0].setTimeForStep(2);
	patternSteps[1].setAction(NONE);
	patternSteps[1].setTimeForStep(1);
	patternSteps[2].setAction(LEFT);
	patternSteps[2].setTimeForStep(2);
	patternSteps[3].setAction(NONE);
	patternSteps[3].setTimeForStep(1);
	patternSteps[4].setAction(TRACK);
	patternSteps[4].setTimeForStep(5);
}

void CollisionTypes::enemyUpDown2()
{
	patternSteps2[0].setAction(LEFT);
	patternSteps2[0].setTimeForStep(2);
	patternSteps2[1].setAction(NONE);
	patternSteps2[1].setTimeForStep(1);
	patternSteps2[2].setAction(RIGHT);
	patternSteps2[2].setTimeForStep(2);
	patternSteps2[3].setAction(NONE);
	patternSteps2[3].setTimeForStep(1);
	patternSteps2[4].setAction(TRACK);
	patternSteps2[4].setTimeForStep(5);
}

void CollisionTypes::enemyLeftRight()
{
	patternSteps3[0].setAction(LEFT);
	patternSteps3[0].setTimeForStep(2);
	patternSteps3[1].setAction(NONE);
	patternSteps3[1].setTimeForStep(1);
	patternSteps3[2].setAction(RIGHT);
	patternSteps3[2].setTimeForStep(2);
	patternSteps3[3].setAction(NONE);
	patternSteps3[3].setTimeForStep(1);
	patternSteps3[4].setAction(TRACK);
	patternSteps3[4].setTimeForStep(5);
}

void CollisionTypes::enemyLeftRight2()
{
	patternSteps4[0].setAction(UP);
	patternSteps4[0].setTimeForStep(2);
	patternSteps4[1].setAction(NONE);
	patternSteps4[1].setTimeForStep(1);
	patternSteps4[2].setAction(DOWN);
	patternSteps4[2].setTimeForStep(2);
	patternSteps4[3].setAction(NONE);
	patternSteps4[3].setTimeForStep(1);
	patternSteps4[4].setAction(TRACK);
	patternSteps4[4].setTimeForStep(5);
}

void CollisionTypes::enemyLeftRight3()
{
	patternSteps5[0].setAction(RIGHT);
	patternSteps5[0].setTimeForStep(2);
	patternSteps5[1].setAction(NONE);
	patternSteps5[1].setTimeForStep(1);
	patternSteps5[2].setAction(LEFT);
	patternSteps5[2].setTimeForStep(2);
	patternSteps5[3].setAction(NONE);
	patternSteps5[3].setTimeForStep(1);
	patternSteps5[4].setAction(TRACK);
	patternSteps5[4].setTimeForStep(5);
}

void CollisionTypes::enemyLeftRight4()
{
	patternSteps6[0].setAction(RIGHT);
	patternSteps6[0].setTimeForStep(2);
	patternSteps6[1].setAction(NONE);
	patternSteps6[1].setTimeForStep(1);
	patternSteps6[2].setAction(LEFT);
	patternSteps6[2].setTimeForStep(2);
	patternSteps6[3].setAction(NONE);
	patternSteps6[3].setTimeForStep(1);
	patternSteps6[4].setAction(TRACK);
	patternSteps6[4].setTimeForStep(5);
}

void CollisionTypes::enemyLeftRight5()
{
	patternSteps7[0].setAction(RIGHT);
	patternSteps7[0].setTimeForStep(2);
	patternSteps7[1].setAction(NONE);
	patternSteps7[1].setTimeForStep(1);
	patternSteps7[2].setAction(LEFT);
	patternSteps7[2].setTimeForStep(2);
	patternSteps7[3].setAction(NONE);
	patternSteps7[3].setTimeForStep(1);
	patternSteps7[4].setAction(TRACK);
	patternSteps7[4].setTimeForStep(5);
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

void CollisionTypes::performEnemyTankPatternStep(int index)
{
	//enemyTanks[index].ai(frameTime, playerTank);
	float distance =  D3DXVec2Length(&(enemyTanks[index].getCenterPoint()-playerTank.getCenterPoint()));
	if  (distance < 200.0f)
	{
		enemyTanks[index].ai(frameTime, playerTank);

		patternStepIndexLvlTwo[index] = 4;
		patternStepsLvl2[index][maxPatternSteps - 1].initialize(&enemyTanks[index]);
		patternStepsLvl2[index][maxPatternSteps - 1].initialize(&enemyTanks[index]);
		patternStepsLvl2[index][maxPatternSteps - 1].setActive();
	}
	else if (patternStepIndexLvlTwo[index] == maxPatternSteps - 1)
	{
		for (int i = 0; i < maxPatternSteps - 1; i++)
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
	patternStepsLvl2[0][4].setAction(TRACK);
	patternStepsLvl2[0][4].setTimeForStep(5);

	patternStepsLvl2[1][0].setAction(RIGHT);
	patternStepsLvl2[1][0].setTimeForStep(2);
	patternStepsLvl2[1][1].setAction(DOWN);
	patternStepsLvl2[1][1].setTimeForStep(1);
	patternStepsLvl2[1][2].setAction(LEFT);
	patternStepsLvl2[1][2].setTimeForStep(2);
	patternStepsLvl2[1][3].setAction(UP);
	patternStepsLvl2[1][3].setTimeForStep(1);
	patternStepsLvl2[1][4].setAction(TRACK);
	patternStepsLvl2[1][4].setTimeForStep(5);


	patternStepsLvl2[2][0].setAction(RIGHT);
	patternStepsLvl2[2][0].setTimeForStep(1);
	patternStepsLvl2[2][1].setAction(UP);
	patternStepsLvl2[2][1].setTimeForStep(1);
	patternStepsLvl2[2][2].setAction(LEFT);
	patternStepsLvl2[2][2].setTimeForStep(1);
	patternStepsLvl2[2][3].setAction(DOWN);
	patternStepsLvl2[2][3].setTimeForStep(1);
	patternStepsLvl2[2][4].setAction(TRACK);
	patternStepsLvl2[2][4].setTimeForStep(5);

	patternStepsLvl2[3][0].setAction(RIGHT);
	patternStepsLvl2[3][0].setTimeForStep(1);
	patternStepsLvl2[3][1].setAction(DOWN);
	patternStepsLvl2[3][1].setTimeForStep(1);
	patternStepsLvl2[3][2].setAction(LEFT);
	patternStepsLvl2[3][2].setTimeForStep(1);
	patternStepsLvl2[3][3].setAction(UP);
	patternStepsLvl2[3][3].setTimeForStep(1);
	patternStepsLvl2[3][4].setAction(TRACK);
	patternStepsLvl2[3][4].setTimeForStep(5);


	patternStepsLvl2[4][0].setAction(RIGHT);
	patternStepsLvl2[4][0].setTimeForStep(2);
	patternStepsLvl2[4][1].setAction(DOWN);
	patternStepsLvl2[4][1].setTimeForStep(1);
	patternStepsLvl2[4][2].setAction(LEFT);
	patternStepsLvl2[4][2].setTimeForStep(2);
	patternStepsLvl2[4][3].setAction(UP);
	patternStepsLvl2[4][3].setTimeForStep(1);
	patternStepsLvl2[4][4].setAction(TRACK);
	patternStepsLvl2[4][4].setTimeForStep(5);

	patternStepsLvl2[5][0].setAction(RIGHT);
	patternStepsLvl2[5][0].setTimeForStep(1);
	patternStepsLvl2[5][1].setAction(RIGHT);
	patternStepsLvl2[5][1].setTimeForStep(1);
	patternStepsLvl2[5][2].setAction(LEFT);
	patternStepsLvl2[5][2].setTimeForStep(1);
	patternStepsLvl2[5][3].setAction(LEFT);
	patternStepsLvl2[5][3].setTimeForStep(1);
	patternStepsLvl2[5][4].setAction(TRACK);
	patternStepsLvl2[5][4].setTimeForStep(5);


	patternStepsLvl2[6][0].setAction(RIGHT);
	patternStepsLvl2[6][0].setTimeForStep(1);
	patternStepsLvl2[6][1].setAction(DOWN);
	patternStepsLvl2[6][1].setTimeForStep(1);
	patternStepsLvl2[6][2].setAction(LEFT);
	patternStepsLvl2[6][2].setTimeForStep(1);
	patternStepsLvl2[6][3].setAction(UP);
	patternStepsLvl2[6][3].setTimeForStep(1);
	patternStepsLvl2[6][4].setAction(TRACK);
	patternStepsLvl2[6][4].setTimeForStep(5);

}
