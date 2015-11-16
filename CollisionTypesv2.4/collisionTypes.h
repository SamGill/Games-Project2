// Programming 2D Games
// Copyright (c) 2011,2012 by: 
// Charles Kelly
// collisionTypes.h v1.0

#ifndef _COLLISION_TYPES_H      // Prevent multiple definitions if this 
#define _COLLISION_TYPES_H      // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

class CollisionTypes;

#include "game.h"
#include "textureManager.h"
#include "image.h"
#include "ship.h"
#include "playerTank.h"
#include "enemyTank.h"
#include "patternStep.h"
#include "wall.h"
#include "murray.h"
#include "gill.h"
#include <cmath>
#include "textDX.h"

#define maxPatternSteps 5

//=============================================================================
// This class is the core of the game
//=============================================================================
class CollisionTypes : public Game
{
private:
	// game items
	TextureManager menuTexture, gameTextures;   // game texture
	Ship    rectangle, square, circle, ship;    // targets and spaceship

	TextureManager tankBodyTexture;
	TextureManager tankCrackOneTexture, tankCrackTwoTexture, tankCrackThreeTexture;
	TextureManager tankHeadTexture;
	TextureManager bulletTexture;
	TextureManager enemyTankTexture;
	TextureManager wallTexture;
	TextureManager splashScreenTexture, gameOverTexture, gameMenuTexture, cheatCodeTexture;
	//Wall texture Managers for level1
	TextureManager wallLgHzTexture, wallShortHzTexture, wallLgVtTexture, wallShortVtTexture;
	TextureManager powerupTexture, enemyBaseTexture;
	TextureManager victoryTexture, instructionsTexture, transitionTexture;
	TextureManager sandTexture;

	//Wall textures for level2
	Wall wallLvl2Vertical[3], wallLvl2Horizontal[4], wallLgHzScreenLvl2;

	Image splashScreen, gameOverScreen, gameMenuScreen, cheatCodeScreen, instructionsScreen, victoryScreen, transitionScreen;
	Image sandScreen;
	//Image wallLgHzScreen, wallLgVtScreen, wallShortHzScreen, wallShortVtScreen;

	PlayerTank     playerTank;
	PlayerTank     crackTwo;
	enemyTank	   enemyTanks[MAX_ENEMY_TANKS];
	enemyTank	   enemyTank;

	Wall           wall;
	Wall		   wallLgHzScreen[LONG_HZ_WALLS], wallLgVtScreen, wallShortHzScreen[SHORT_HZ_WALLS], wallShortVtScreen[SHORT_VT_WALLS];
	murray		   powerup;
	gill		   enemyBase;

	TextDX		   *scoreFont;
	TextDX		   *finalScoreFont;



	GameStates gamestates;

	bulletType bullet_type;

	int score;

	Image   menu;               // menu image
	bool    menuOn;
	VECTOR2 collisionVector;    // collision vector
	Image   line;               // for drawing collision vector
	float   lineRadians;
	float   lineScale;          // distance/LINE_LENGTH
	float   AxBx;
	float   AyBy;
	float   lineLength;

	VECTOR2 lineEnds[2];        // x,y of line endpoints
	PatternStep patternSteps[maxPatternSteps];
	PatternStep patternSteps2[maxPatternSteps];
	PatternStep patternSteps3[maxPatternSteps];
	PatternStep patternSteps4[maxPatternSteps];
	PatternStep patternSteps5[maxPatternSteps];
	PatternStep patternSteps6[maxPatternSteps];
	PatternStep patternSteps7[maxPatternSteps];

	int patternStepIndex;
	int patternStepIndex2;
	int patternStepIndex3;
	int patternStepIndex4;
	int patternStepIndex5;
	int patternStepIndex6;
	int patternStepIndex7;


	float timeInState;

	//For audio
	bool isMusicPlaying;

	//For level one base
	bool isBaseOneDead;
	bool isBaseTwoDead;

	bool havePowerUp;

	bool isLaserPlaying;
	bool isCannonPlaying;
	bool isPowerupPlaying;

	bool level2Cheat;

	//Level two patternSteps
	PatternStep patternStepsLvl2[MAX_ENEMY_TANKS][maxPatternSteps];
	int patternStepIndexLvlTwo[MAX_ENEMY_TANKS];

	void performEnemyTankPatternStep(int index);

	void initializeLvlTwoPatterns();

public:
	// Constructor
	CollisionTypes();

	// Destructor
	virtual ~CollisionTypes();

	// Initialize the game
	void initialize(HWND hwnd);
	void update();      // must override pure virtual from Game
	void ai();          // "
	void collisions();  // "
	void render();      // "
	void releaseAll();
	void resetAll();

	void gameStatesUpdate();

	void enemyUpDown();
	void enemyUpDown2();
	void enemyLeftRight();
	void enemyLeftRight2();
	void enemyLeftRight3();
	void enemyLeftRight4();
	void enemyLeftRight5();
};

#endif
