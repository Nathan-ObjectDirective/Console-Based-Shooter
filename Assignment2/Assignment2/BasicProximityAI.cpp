#include "BasicProximityAI.h"
#include <Windows.h>

BasicProximityAI::BasicProximityAI()
{
	m_aggressionRange = 6; // Hard-coded for now.
	m_pTarget = 0;
}

BasicProximityAI::~BasicProximityAI()
{
	m_pTarget = 0; // Clear dangling pointer.
}

// Set the target of the AI.
void BasicProximityAI::setTarget(GameObject* pTarget)
{
	m_pTarget = pTarget;
}

// Get the coordinates of the target.
pair<int, int> BasicProximityAI::getTargetLocation()	
{
	return m_pTarget->getCoords();
}

// Is the Enemy within and m_aggressionRange*m_aggressionRange Range of the Player.
bool BasicProximityAI::isTargetWithinRange(pair<int, int> coordsToCompare)
{
	pair<int, int> coords = xYAdjustForTarget(coordsToCompare);

	
	if ((coords.first >= (m_aggressionRange*-1) && coords.first <= m_aggressionRange) && (coords.second >= (m_aggressionRange*-1) && coords.second <= m_aggressionRange))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Amount of adjust to reach target.
pair<int, int> BasicProximityAI::xYAdjustForTarget(pair<int, int> coords)
{
	pair<int, int> targetLocation = getTargetLocation();
	const pair<int, int> searcherLocation = coords;

	int xAdjust = searcherLocation.first - targetLocation.first; // Amount of X to adjust to land on target
	int yAdjust = searcherLocation.second - targetLocation.second; // Amount of Y to adjust to land on target

	pair<int, int> xYAdjust = make_pair(xAdjust, yAdjust);

	return xYAdjust;
}

// Calculate the apporach between the target and the searching object
pair<int, int> BasicProximityAI::calcApproachToTarget(GameObject * searchingGameObject)
{
	pair<int, int> coords = xYAdjustForTarget(searchingGameObject->getCoords());

	pair<int, int> moveUpdate;

	if (abs(coords.first) > abs(coords.second)) // If the enemy's x axis is closer to the player than their y axis
	{
		if (coords.first < 0) // If the enemy is left of the player
		{
			moveUpdate.first = 1; // Move Right 1 Tile
		}
		else if (coords.first > 0) // If the enemy is right of the player
		{
			moveUpdate.first = -1; // Move Left 1 Tile
		}
	}
	else if (abs(coords.first) < abs(coords.second)) // If the enemy's y axis is closer to the player than their x axis
	{
		if (coords.second < 0) // If the enemy is below  the player
		{
			moveUpdate.second = 1; // Move Up 1 Tile
		}
		else if (coords.second > 0) // If the enemy is above the player
		{
			moveUpdate.second = -1; // Move Down 1 Tile
		}
	}
	else // If the enemy's x axis is the same distance to the player as their y axis
	{
		const int pick = rand() % 2;

		if (pick == 0)
		{
			if (coords.first < 0) // If the enemy is left of the player
			{
				moveUpdate.first = 1;
			}
			else if (coords.first > 0) // If the enemy is right of the player
			{
				moveUpdate.first = -1;
			}
		}
		else if (pick == 1)
		{
			if (coords.second < 0) // If the enemy is below  the player
			{
				moveUpdate.second = 1;
			}
			else if (coords.second > 0) // If the enemy is above the player
			{
				moveUpdate.second = -1;
			}
		}

	}

	return moveUpdate;
}