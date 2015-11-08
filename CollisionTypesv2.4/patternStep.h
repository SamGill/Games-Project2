
              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN
#ifndef PATTERN_STEM_H                 // Prevent multiple definitions if this 
#define PATTERN_STEM_H   



//class PatternStep;

#include "constants.h"
#include "entity.h"
#include "enemyTank.h"
#include <cmath>
#include <d3d9.h>
#include <d3dx9.h>

namespace patternStepNS
{
}

class PatternStep
{
private:
 
    bool active;                  
	enemyTank* entity;
	float timeInStep; //accumulates the time step has executed
	float timeForStep; //limit on the time for the step
	PATTERN_STEP_ACTION action;

public:
    PatternStep();
	void initialize(enemyTank *e);
    void update(float frameTime);
	void setEntity(enemyTank *e) {entity = e;}
	void setAction(PATTERN_STEP_ACTION a) {action = a;}
	void setTimeForStep(float time) {timeForStep = time;}
	bool isFinished() {return !active;}
	void setActive() {active = true;}
	void setInactive() {active = false;}
};
#endif



