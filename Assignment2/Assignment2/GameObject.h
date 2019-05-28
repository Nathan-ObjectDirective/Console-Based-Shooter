#pragma once
#ifndef GAMEOBJECT_H 
#define GAMEOBJECT_H

#define MINCOORDVALUE 0
#define MAXCOORDVALUE 9
#define NUMCARDINALDIRECTIONS 4

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum Direction { Up = 0, Right = 1, Down = 2, Left = 3 }; // Used lower case to avoid clashes with macros.

class GameObject
{

public:
	GameObject(); 
	~GameObject();

	// Quick overloaded ostream operator to send the GameObject as an output statement, printing its TypeID.
	friend ostream& operator<<(ostream& os, const GameObject& aGameObject);

	void draw() const; // print to the screen the typeID and its x and y coords
	void info() const; // print all info relating to the object
	void spawn(std::string typeID, int health, int speed, int x, int y, char name); // Initialise an object.
	void setDisposition(bool disposition); // Sets the GameObject passive or aggressive.
	void takeDamage(int health); // Receive Damage from something else.

	virtual void update() = 0; //virtual function

	// These will be refactoring into an input handler.
	virtual void controlManualAction() = 0;
	virtual void controlAutoMovement(pair <int, int>) = 0;

	bool isAlive() const; // Return true if its health is greater than 0.
	bool isShooting(); // Return true if the Player took a shot in the last turn.

	char getName() const;

	int getHealth() const;

	pair <int, int> getCoords(); // Get coordinates.

	// These will be refactored into a bullet handler.
	virtual vector<pair<int, int>> getShotDetails() = 0;
	virtual vector<pair<int, int>> shoot() = 0;

protected:
	char m_name;

	bool m_isPassive; 
	bool m_isShooting;

	int m_health;
	int m_speed; // Value between 1 and 4.
	int m_x;
	int m_y;
	int m_healthDrain;

	vector<pair<int, int>> m_vShotDetails; // Where the Player shot in the last turn.
	string m_typeID;

	Direction direction; // The direction on the board that the GameObject is going.
};

#endif