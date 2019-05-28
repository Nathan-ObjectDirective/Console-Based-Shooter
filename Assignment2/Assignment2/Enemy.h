#pragma once
#ifndef ENEMY_H 
#define ENEMY_H

#include "GameObject.h"
#include "Game.h"

class Enemy: public GameObject
{
public:
	Enemy();
	~Enemy();

	void determineMovement(); // AI influenced determination.
	void performPassiveMovement(); // Run around back and forth on the board.
	void performAgressiveMovement(); // Slow down and hunt the Player.

	virtual void update();
	virtual void controlManualAction(); // Tell the Enemy where to go.
	virtual void controlAutoMovement(pair <int, int>); // The Enemy decides for itself where to go.
	
	virtual vector<pair<int, int>> getShotDetails(); // Load up any incoming bullets, the functionality behind this can be improved a lot.

private:
	virtual vector<pair<int, int>> shoot(); // Not yet implemented for this Enemy Class.
	int m_updates;

	pair<int, int> m_autoMovementAdjust; // The movement to adjust for to chase the Player.
};
#endif