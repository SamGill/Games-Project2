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
#include <cmath>


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
	TextureManager tankHeadTexture;
	TextureManager bulletTexture;
	TextureManager enemyTankTexture;
	TextureManager wallTexture;
	TextureManager splashScreenTexture, gameOverTexture, gameMenuTexture, cheatCodeTexture;
	TextureManager wallLgHzTexture, wallShortHzTexture, wallLgVtTexture, wallShortVtTexture;

	Image splashScreen, gameOverScreen, gameMenuScreen, cheatCodeScreen;
	//Image wallLgHzScreen, wallLgVtScreen, wallShortHzScreen, wallShortVtScreen;

	PlayerTank     playerTank;
	enemyTank	   enemyTanks[MAX_ENEMY_TANKS];
	enemyTank	   enemyTank;
	Wall           wall;
	Wall		   wallLgHzScreen, wallLgVtScreen, wallShortHzScreen, wallShortVtScreen;

	GameStates gamestates;


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
	int patternStepIndex;
	float timeInState;

	//For audio
	bool isMusicPlaying;

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
};

#endif
