#pragma once
#include "CGameObject.h"

/**
* @brief Represents an asteroid in the game
*
* This class implements asteroids with random size, color, position,
* and velocity. Includes functionality to spawn safely away from
* the player's ship.
*
* @author Johnny Liu
*/
class CAstroid : public CGameObject
{
public:
	/**
	* @brief Default constructor for CAstroid
	* 
	* Initializes asteroid with random size (10-80), random position,
	* random color, and random velocity (-5 to 5 in x and y)
	*/
	CAstroid();
	
	/**
	* @brief Parameterized constructor for CAstroid
	* 
	* @param _size The radius of the asteroid in pixels
	* @param _intitalPosition The initial position of the asteroid
	* @param _initialVelocity The initial velocity vector of the asteroid
	*/
	CAstroid(int _size, cv::Point2f _intitalPosition, cv::Point2f _initialVelocity);
	
	/**
	* @brief Destructor for CAstroid
	*/
	~CAstroid();

	/**
	* @brief Ensures asteroid spawns at a safe distance from the ship
	* 
	* Regenerates asteroid position until it is at least min_distance
	* away from the ship's position. Limits attempts to 100 to prevent
	* infinite loops.
	* 
	* @param ship_pos The current position of the player's ship
	* @param min_distance Minimum safe distance in pixels from the ship
	* @return void
	*/
	void ensure_safe_spawn(cv::Point2f ship_pos, float min_distance);

protected:
	int _size; ///< Radius of the asteroid in pixels
	cv::Point2i _initialPosition; ///< Starting position when asteroid was created
	cv::Point2i _initialVelocity; ///< Starting velocity when asteroid was created
};
