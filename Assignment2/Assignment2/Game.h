#pragma once
#ifndef GAME_H 
#define GAME_H

#include <time.h>
#include <list>
#include <regex>
#include <memory>

#include "Enemy.h"
#include "Player.h"
#include "GameBoard.h"
#include "BasicProximityAI.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "LevelChangeState.h"

class Game
{

public:
	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}

		return s_pInstance;
	}

	GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

	void quit() { }//m_isGameRunning = false; }

	bool init(); // create the objects and assign each enemy and player unique typeID, health and x and y coords max health should be 160, speed is between 1 and 4
		 // place the objects on the list
	void draw(); // cycle through the enemy and player objects and call the draw function for each object
	void update(); //cycle through the enemy and player objects and call the update function for each object
	void battle(); // if two objects occupy the same coords declare a battle must take  place. The object with the higher health wins. The loser will have its health set to 0.
	void info(); // cycle through the enemy and player objects and call the info function for each object
	void clean(); //remove any objects from the list whose health is 0 
	void displayBoard();
	void initBoard();
	bool winConditionCheck();
	void enemyKilled();
	void advanceFrame();
	void beginLevel();
	void endLevel();

	int getLevel();

	bool isRunning();
	
private:
	void assignSafeSpace(pair <int, int> playerPosition, int range); // Create a safe area around the player when he spawns into the map
	void generateEnemies(); // Generate the enemies
	void configurePlayer(); // Configure the player
	void checkEnemyActions(list<GameObject*>::iterator it); // Check the results of the actions taken by enemies
	void checkPlayerActions(list<GameObject*>::iterator it); // Check the results of the actions taken by the player
	void isEnemyHit(vector < pair<int, int>> hitScan); // Check if the enemy was hit by the player

	GameStateMachine* m_pGameStateMachine;

	int getNumEnemiesInput(); // Take in the amount of enemies to spawn, unused.
	int m_enemiesKilled; // The amount of enemies the player managed to kill
	int m_level; // The current level
	bool m_killedByEnemy; // We need to know if the player was killed by an enemy or the end level clean function

	bool m_enemyKilled; // Was an enemy killed last update
	bool m_isGameRunning; 
	unique_ptr<GameBoard> m_pGameBoard;
	unique_ptr<BasicProximityAI> m_pBasicProximityAI;

	pair <int, int> genRandUniqueCoords(); // Generate unique random coordinates for all game objects
	static vector<pair<int, int>> m_vUniqueXYCoordinates;
	list<GameObject*> vpGameObjects;

	static Game* s_pInstance;

	Game();
	~Game();
};
typedef Game TheGame;
#endif
