#pragma once

#include "CGameObject.h"

/**
* @brief Represents a missile fired by the player's ship
*
* This class implements projectiles that travel in a straight line
* at constant velocity. Missiles have no speed cap and simple
* movement behavior.
*
* @author Johnny Liu
*/
class CMissile : public CGameObject
{
public:
	/**
	* @brief Default constructor for CMissile
	* 
	* Initializes missile with radius of 5 and 1 life
	*/
	CMissile();
	
	/**
	* @brief Destructor for CMissile
	*/
	~CMissile();
	
	/**
	* @brief Updates missile position
	* 
	* Overrides base move method to provide uncapped velocity
	* for fast projectile movement
	* @return void
	*/
	void move();
};