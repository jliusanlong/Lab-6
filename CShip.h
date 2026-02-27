#pragma once
#include "CGameObject.h"

/**
* @brief Represents the player's ship in the Asteroids game
*
* This class implements the player-controlled ship with configurable size,
* lives, position, and facing direction. Inherits physics and collision
* behavior from CGameObject.
*
* @author Johnny Liu
*/
class CShip : public CGameObject
{
public:
	/**
	* @brief Default constructor for CShip
	* 
	* Initializes ship with default radius of 20, 10 lives,
	* centered position, and upward facing direction
	*/
	CShip();
	
	/**
	* @brief Parameterized constructor for CShip
	* 
	* @param _size The radius of the ship in pixels
	* @param _lives The number of lives the ship starts with
	*/
	CShip(int _size, int _lives);
	
	/**
	* @brief Destructor for CShip
	*/
	~CShip();
};