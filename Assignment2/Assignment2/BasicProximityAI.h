#pragma once
#ifndef BASICPROXIMITYAI_H
#define BASICPROXIMITYAI_H

#include "GameObject.h"

class BasicProximityAI 
{
public:
	
	BasicProximityAI();
	~BasicProximityAI();

	void setTarget(GameObject* target); // Set the target of the AI.
	
	pair<int, int> calcApproachToTarget(GameObject* searchingGameObject); // Get the needed x or y value to approach the target.

	bool isTargetWithinRange(pair<int, int> coordsToCompare);  // Is the Enemy within and m_aggressionRange*m_aggressionRange Range of the Player.
	

private:
	GameObject* m_pTarget;

	int m_aggressionRange;
	pair<int, int> getTargetLocation(); // Get the coordinates of the target.
	pair<int, int> xYAdjustForTarget(pair<int, int>); // Amount of adjust to reach target.
};
#endif