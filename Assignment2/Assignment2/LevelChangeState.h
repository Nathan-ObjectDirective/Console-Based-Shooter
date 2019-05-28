#pragma once
#ifndef LEVELCHANGESTATE_H
#define LEVELCHANGESTATE_H

#include <iostream>
#include <vector>
#include "MenuState.h"
#include "Game.h"
#include "PlayState.h"


// This class allows playstate to refresh after a level is complete.
class LevelChangeState : public GameState
{
public:

	virtual ~LevelChangeState() {}

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_transitionID; }

private:

	static const std::string s_transitionID;

	std::vector<GameObject*> m_gameObjects;
};


#endif 
