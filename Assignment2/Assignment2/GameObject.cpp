#include "GameObject.h"

// Initialising variables.
GameObject::GameObject()
{
	m_healthDrain = 0;
	m_isPassive = true;
	m_typeID = "";
	m_health = 0;
	m_speed = 0;
	m_isShooting = false;

	m_x = 0;
	m_y = 0;

	m_name = '?'; 

	direction = Up;
}

GameObject::~GameObject()
{
}

// Initialise an object.
void GameObject::spawn(std::string typeID, int health, int speed, int x, int y, char name)
{
	m_typeID = typeID;
	m_health = health;
	m_speed = speed;

	m_x = x;
	m_y = y;

	m_name = name;
}
 
void GameObject::draw() const // print to the screen the typeID and its x and y coords
{
	cout << " TypeID: " << m_typeID << ": \tX: " << m_x << " Y: " << m_y << endl;
}

void GameObject::info() const // print all info relating to the object
{
	cout << " ID: " << m_typeID << " \tHealth: " << m_health << " \tSpeed: " << m_speed  << " \tX: " << m_x << " Y: " << m_y << endl;
}

bool GameObject::isAlive() const
{
	bool alive = true; 

	if (m_health <= 0)
	{
		alive = false;
	}

	return alive;
}

pair<int, int> GameObject::getCoords() 
{
	return make_pair(m_x, m_y);
}

void GameObject::setDisposition(bool disposition) // Sets the GameObject passive or aggressive.
{
	m_isPassive = disposition;
}

void GameObject::takeDamage(int damage) // Receive Damage from something else.
{
	if (m_health - damage < 0)
	{
		m_health = 0;
	}
	else 
	{
		m_health -= damage;
	}
}

char GameObject::getName() const
{
	return m_name;
}

int GameObject::getHealth() const
{
	return m_health;
}

bool GameObject::isShooting()
{
	return m_isShooting;
}

// Quick overloaded ostream operator to send the GameObject as an output statement, printing its TypeID.
ostream & operator<<(ostream & os, const GameObject & aGameObject)
{
	os << "GameObject Object - ";
	os << "m_typeID: " << aGameObject.m_typeID;
	return os;
}
