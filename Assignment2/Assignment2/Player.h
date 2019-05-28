#pragma once
#ifndef PLAYER_H 
#define PLAYER_H

#include "GameObject.h"
#include "InputHandler.h"
#include "SoundManager.h"

class Player: public GameObject 
{
public:
	Player();
	~Player();
	
	virtual void controlManualAction(); // User tells the player what to do.
	virtual void controlAutoMovement(pair <int,int>); // Not yet implemented for this Player Class.
	
	virtual vector<pair<int, int>> getShotDetails(); // Player returns where he shot.

	void movePlayer(); // User has told the Player to move.

private:
	virtual vector<pair<int, int>> shoot(); // User has told the Player to shoot.
	virtual void update();

	int bulletCounter;
};
#endif