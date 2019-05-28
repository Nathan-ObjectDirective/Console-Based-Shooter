#include "Game.h"

Game* Game::s_pInstance = 0;

vector<pair<int, int>> Game::m_vUniqueXYCoordinates; // Instantiating our vector of unique coordinates.

Game::Game()
{
	m_pGameBoard = make_unique<GameBoard>(); // Make a smart pointer to the created GameBoard object memory location.
	m_pBasicProximityAI = make_unique<BasicProximityAI>(); // Make a smart pointer to the created GameBoard object memory location.
	m_isGameRunning = false;
	m_killedByEnemy = false;
	m_level = 1;
}

Game::~Game()
{
	m_pGameBoard.reset(); // Release GameBoard resource in Game destructor.
	m_pGameBoard = 0; // Clear dangling pointer.

	m_pBasicProximityAI.reset(); // Release GameBoard resource in Game destructor.
	m_pBasicProximityAI = 0; // Clear dangling pointer.
}

// Initialise the key components of Game.
bool Game::init()
{
	// Load the sound files into the game
	TheSoundManager::Instance()->load("assets/AssaultOnMistCastle.ogg", "soundTrack", SOUND_MUSIC);
	TheSoundManager::Instance()->load("assets/zombie.wav", "zombie", SOUND_SFX);
	TheSoundManager::Instance()->load("assets/shotgun.ogg", "shotgun", SOUND_SFX);

	// Play the main track
	TheSoundManager::Instance()->playMusic("soundTrack", -1);

	// Turn on the controller
	TheInputHandler::Instance()->initialiseJoysticks();

	m_pGameStateMachine = new GameStateMachine();

	// Load the initial menu state
	m_pGameStateMachine->changeState(new MainMenuState());

	m_isGameRunning = true; // Critical components are initialised, begin the main loop.

	return true;
}


void Game::beginLevel()
{
	m_pGameBoard->initBoard(); // Initialise the board, fill it with empty spaces.

	configurePlayer(); // Spawn the player and configure him.
	generateEnemies(); // Generate an input amount of Enemies.

	// Push initial starting coords to the board.
	for (list<GameObject*>::iterator it = vpGameObjects.begin(); it != vpGameObjects.end(); it++)
	{
		m_pGameBoard->updateBoard((*it)->getCoords(), (*it)->getName());
	}

	displayBoard();
}

void Game::endLevel()
{
	// Increment the level counter
	m_level++;

	// Reduce all game objects to 0 health to be destroyed
	for (list<GameObject*>::iterator it = vpGameObjects.begin(); it != vpGameObjects.end(); it++)
	{
		(*it)->takeDamage((*it)->getHealth()); // Kill the player. Getting attacked by a Zombie is a one hit kill.
	}

	// Clear the storage of coordinates
	m_vUniqueXYCoordinates.clear();
	
	// Destroy all game objects
	clean();
}

int Game::getLevel()
{
	return m_level;
}

// Call the draw function of our GameObjects.
void Game::draw()
{
	list<GameObject*>::iterator it;
	for (it = vpGameObjects.begin(); it != vpGameObjects.end(); it++)
	{
		(*it)->draw();
	}
}

// Call the game state update
void Game::update()
{
	m_pGameStateMachine->update();
}

// Check if the Enemy has eaten the Player.
void Game::battle() // This implementation is messy and needs improvement.
{
	int enemyX; 
	int enemyY;

	// For each object.
	for (list<GameObject*>::iterator it = vpGameObjects.begin(); it != vpGameObjects.end(); it++)
	{
		// If it is an Enemy
		if ((*it)->getName() == 'Z')
		{
			//Track the coordinates.
			enemyX = (*it)->getCoords().first;
			enemyY = (*it)->getCoords().second;

			// For each object to compare against.
			for (list<GameObject*>::iterator it = vpGameObjects.begin(); it != vpGameObjects.end(); it++)
			{
				// If it is a Player and the Enemy is on the same tile.
				if (((*it)->getName() == 'P') && ((enemyX == (*it)->getCoords().first) && (enemyY == (*it)->getCoords().second)))
				{
					(*it)->takeDamage((*it)->getHealth()); // Kill the player. Getting attacked by a Zombie is a one hit kill.
					TheSoundManager::Instance()->playSound("zombie", 0);
					m_killedByEnemy = true;
				}
			}
		}
	}	
}

// Call the info function of our GameObjects, printing them to the screen.
void Game::info()
{
	cout << endl;
	cout << "Level: " << m_level << endl;
	cout << "Enemies killed: " << m_enemiesKilled << endl << endl;

	list<GameObject*>::iterator it;
	for (it = vpGameObjects.begin(); it != vpGameObjects.end(); it++)
	{
		(*it)->info();
	}

}

// Clean up our resources on GameObject Death.
void Game::clean()
{
	for (list<GameObject*>::iterator itr = vpGameObjects.begin(); itr != vpGameObjects.end(); )
	{
		// End Game Lose Condition 2
		if ((*itr)->getName() == 'P' && (!(*itr)->isAlive()) && m_killedByEnemy)
		{
			m_isGameRunning = false;

			cout << "\n \t\tOh no, you have been eaten by a zombie!\n" << endl;

			info();

			delete *itr;
			itr = vpGameObjects.erase(itr);
		}
		else if ((*itr)->getName() == 'P' && (!(*itr)->isAlive()))
		{
			delete *itr;
			itr = vpGameObjects.erase(itr);
		}
		else if (!(*itr)->isAlive())
		{
			delete *itr;
			itr = vpGameObjects.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

// Display our board.
void Game::displayBoard()
{
	m_pGameBoard->displayBoard();
}

void Game::initBoard()
{
	m_pGameBoard->initBoard();
}

bool Game::winConditionCheck()
{
	if ((vpGameObjects.size() == 1) && (vpGameObjects.front()->getName() == 'P'))
	{
		cout << "\n\n\n\tWell fought Soldier, all the Zombies have been defeated!\n\n" << endl;

		m_pGameStateMachine->changeState(new LevelChangeState());
		m_pGameStateMachine->update();

		return true;
	}
	else
	{
		return false;
	}
}

// Return the state of the game.
bool Game::isRunning()
{
	return m_isGameRunning;
}

// Generate a pair of guaranteed random unique coordinates.
pair <int, int> Game::genRandUniqueCoords()
{
	bool uniqueCoordsFound = false;

	pair<int, int> generatedCoords;

	int x = 0;
	int y = 0;

	while (!uniqueCoordsFound)
	{
		x = rand() % (MAXCOORDVALUE + 1); // Value between 0 and 9.
		y = rand() % (MAXCOORDVALUE + 1);

		// Some critical error checking.
		if (((x < MINCOORDVALUE) || (x > MAXCOORDVALUE)) || ((y < MINCOORDVALUE) || (y > MAXCOORDVALUE)))
		{
			throw std::invalid_argument("x and y coordinates must each be between 1 and 10.");
		}
		else
		{
			generatedCoords.first = x; // Put the x into the first of our pair.
			generatedCoords.second = y; // Put the y into the second of our pair.
		}

		// Compare the pair to what we have already generated from before, If the coordinates are not in our static vector.
		if (find(m_vUniqueXYCoordinates.begin(), m_vUniqueXYCoordinates.end(), generatedCoords) == m_vUniqueXYCoordinates.end())
		{
			m_vUniqueXYCoordinates.push_back(generatedCoords); // All good to push the coordinates onto the vector so they won't get used again.
			uniqueCoordsFound = true;
		}
	}

	return generatedCoords; // Return our unique coordinates.
}

/*
	Sets aside a safeSpaceRange*safeSpaceRange grid around the player that Enemies cannot spawn in.
	This will allow the player a safe area in which to start playing in.
*/
void Game::assignSafeSpace(pair<int, int> playerPosition, int range)
{
	const int safeSpaceRange = range;

	// For the range around the Player. TODO, do not consider Player's position.
	for (int i = playerPosition.first - safeSpaceRange; i < playerPosition.first + safeSpaceRange; i++)
	{
		for (int j = playerPosition.second - safeSpaceRange; j < playerPosition.second + safeSpaceRange; j++)
		{
			m_vUniqueXYCoordinates.push_back(make_pair(i, j));
		}
	}
}

void Game::generateEnemies()
{
	pair <int, int> enemyCoords;

	const int numEnemies = 8;//getNumEnemiesInput(); // Get our number of Enemies input.

	for (int i = 0; i < numEnemies; i++)
	{
		Enemy* pEnemy = 0;
		pEnemy = new Enemy();

		enemyCoords = genRandUniqueCoords(); // Store some unique coordinates.

		// Concatenate "Enemy" with i+1, so that the Enemy will have an int id after their name as well.
		string idConcat = "Zombie " + to_string(i+1); 

		// Pass in our concatenation, some default health and speed values as well as our unique coordinates and name.
		pEnemy->spawn(idConcat, 160, 1, enemyCoords.first, enemyCoords.second, 'Z'); 

		vpGameObjects.push_back(pEnemy);
	}
}

// Run required Player configuration.
void Game::configurePlayer()
{
	pair <int, int> playerStartPosition = genRandUniqueCoords(); // Give them unique coordinates.

	Player* pPlayer = 0;
	pPlayer = new Player();

	pPlayer->spawn("Player", 160, 1, playerStartPosition.first, playerStartPosition.second, 'P');
	m_pBasicProximityAI->setTarget(pPlayer); // Set the player as the target of all other entities for AI, for now.

	int safeSpaceRange = 4;

	// Assign our safe space.
	assignSafeSpace(playerStartPosition, safeSpaceRange); 

	vpGameObjects.push_back(pPlayer);
}

// Check what the Enemy has done during their update and adjust for next update.
void Game::checkEnemyActions(list<GameObject*>::iterator it)
{
	bool isEnemyPassive = false;

	// If the Enemy is within range of the Player.
	if ( m_pBasicProximityAI->isTargetWithinRange( (*it)->getCoords() ) )
	{
		isEnemyPassive = false;
		(*it)->setDisposition(isEnemyPassive);

		pair <int, int> adjustmentCoords;

		// Hunt down the Player.
		adjustmentCoords = m_pBasicProximityAI->calcApproachToTarget(*it);
		(*it)->controlAutoMovement(adjustmentCoords);
	}
	else // Go back to or continue passive patrol routine.
	{
		isEnemyPassive = true;
		(*it)->setDisposition(isEnemyPassive);
	}
}

// Check what the Player has done during their update and adjust for next update.
void Game::checkPlayerActions(list<GameObject*>::iterator it)
{
	// If the Player was shooting.
	if ( (*it)->isShooting() )
	{
		vector <pair<int, int>> shotDetails = (*it)->getShotDetails(); // Get the details of the bullet spread.
		
		vector<pair<int, int>>::iterator bullets;

		for (bullets = shotDetails.begin(); bullets != shotDetails.end(); bullets++)
		{
			m_pGameBoard->updateBoard(*bullets, '*'); // Update our board with where the Player shot.
		}

		isEnemyHit(shotDetails); // Will an Enemy be hit by the bullets. 
	}
}


// Check if the Enemy has been hit by any bullets in the last update.
void Game::isEnemyHit(vector<pair<int, int>> hitScan)
{
	
	for (list<GameObject*>::iterator itr = vpGameObjects.begin(); itr != vpGameObjects.end(); itr++)
	{	// For every Enemy.
		if ((*itr)->getName() == 'Z')
		{
			for (vector< pair<int, int>>::iterator it = hitScan.begin(); it != hitScan.end(); it++)
			{	
				// Check if the Enemy was situated in the spread of the bullets that the Player shot.
				if ((*it) == (*itr)->getCoords())
				{
					(*itr)->takeDamage((*itr)->getHealth()); // Kill them if it was true.

					m_enemyKilled = true; // Set off our narrator to say that a Zombie was killed. TODO Improve this by sending back how many were killed.
					m_enemiesKilled++;
					//m_pGameBoard->updateBoard((*itr)->getCoords(), ' '); // Player an empty tile where the Enemy died.
				}
			}
		}

	}
}

// Send out some dialogue on Enemy Killed.
void Game::enemyKilled()
{
	if (m_enemyKilled)
	{
		int pickQuote = rand() % 3; // Randomly pick between 3 quotes.

		if (pickQuote == 0)
		{
			cout << "\n Zombie down! Nice Shot!" << endl;
		}
		else if (pickQuote == 1)
		{
			cout << "\n Zombie down! Look at the guts fly!" << endl;
		}
		else if (pickQuote == 2)
		{
			cout << "\n Zombie down! CARNAGE!" << endl;
		}

		m_enemyKilled = false;
	}
}

/*Update the game by initialising the board again, check if any enemies have been killed and show that,
Call the update functions of our GameObjects, push their coords to the screen if they are alive.
Check the actions as a result of updating for the player and enemy and then finally display the board.*/
void Game::advanceFrame()
{
	const char emptyTile = ' ';

	// End Game Win Condition

	if (winConditionCheck())
	{
		return;
	}

	// Clearing the old positions taken by entities, this needs to be improved.
	initBoard();

	// Print out some text to encourage the Player on Enemy kill.
	enemyKilled();

	for (list<GameObject*>::iterator it = vpGameObjects.begin(); it != vpGameObjects.end(); it++)
	{
		(*it)->update(); // Call the update functions of our GameObjects

		// Push their coords to the screen if they are alive.
		if ((*it)->getHealth() != 0)
		{
			m_pGameBoard->updateBoard((*it)->getCoords(), (*it)->getName());
		}
	}

	// Check the actions as a result of updating the Player and Enemy
	for (list<GameObject*>::iterator it = vpGameObjects.begin(); it != vpGameObjects.end(); it++)
	{
		if ((*it)->getName() == 'P')
		{
			checkPlayerActions(it);
		}
		if ((*it)->getHealth() != 0) // Update our Board again.
		{
			m_pGameBoard->updateBoard((*it)->getCoords(), (*it)->getName());
		}
		if ((*it)->getName() == 'Z')
		{
			checkEnemyActions(it);
		}		
	}

	// Display the board.
	TheGame::Instance()->displayBoard(); // This must display last.
}

// Get the input for the number of Enemies to spawn.
int Game::getNumEnemiesInput()
{
	bool inputValidated = false;

	string userInput = "";

	// Builds a regular expression that has a digit from 1-9 at the start and then any amount of digits 0-9 thereafter
	regex validInput{ "[1-9][0-9]*" };
	smatch stringMatch; // Create the string matcher object.

	int numEnemiesInput = 0;

	do
	{
		cout << "\n\tHow many enemies would you like to train against? Max: 6 Min: 1." << endl;
		cout << "\tAmount: ";

		getline(cin, userInput); // To get the entire input, including spaces.

		if (!regex_match(userInput, stringMatch, validInput)) // If the string input does not match the regular expression.
		{
			cout << "\t Invalid input." << endl;

		}
		else // We can convert the string to an integer and test if it is within the 1-6 range.
		{
			numEnemiesInput = strtol(userInput.c_str(), NULL, 10);

			const int maxEnemies = 6;
			const int minEnemies = 1;

			if (numEnemiesInput > maxEnemies)
			{
				cout << numEnemiesInput << " is too many enemies, the Maximum is 6." << endl;
			}
			else if (numEnemiesInput < minEnemies)
			{
				// While this code will never be reached due to the regular expression, it is there for future proofing.
				cout << numEnemiesInput << " is too few enemies, the Minimum is 1." << endl; 
			}
			else // Input validation is complete.
			{
				cout << "\n Spawning " << numEnemiesInput << " enemies!" << endl;

				inputValidated = true;
			}
		}
	} while (!inputValidated); // While the input is not valid.

	return numEnemiesInput;
}