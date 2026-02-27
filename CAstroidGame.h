#pragma once

#include "CBase4618.h"
#include "CShip.h"
#include "CAstroid.h"
#include "CMissile.h"
#include <vector>

/**
* @brief Implements the classic Asteroids arcade game
*
* This class creates an interactive Asteroids game with ship physics,
* asteroid spawning, missile firing, collision detection, scoring,
* and game state management including lives and invincibility frames.
*
* @author Johnny Liu
*/
class CAstroidGame : public CBase4618
{
public:
	/**
	* @brief Constructor for CAstroidGame
	* 
	* Initializes game with ship, 10 asteroids, timers, and score
	* 
	* @param comport The COM port number for microcontroller communication
	* @param rows The number of rows for the canvas
	* @param cols The number of columns for the canvas
	*/
	CAstroidGame(int comport, int rows, int cols);
	
	/**
	* @brief Destructor for CAstroidGame
	*/
	~CAstroidGame();
	
	/**
	* @brief Main game loop
	* 
	* Runs the continuous loop for the Asteroids game,
	* handling input, updates, and rendering until exit
	* @return void
	*/
	void run();
	
	/**
	* @brief Reads GPIO inputs from the microcontroller
	* 
	* Retrieves joystick position and button states for ship control
	* @return void
	*/
	void gpio();
	
	/**
	* @brief Updates game state
	* 
	* Processes ship movement with physics, asteroid movement, missile firing,
	* collision detection (ship-asteroid, missile-asteroid), invincibility frames,
	* asteroid spawning timer, and game reset
	* @return void
	*/
	void update();
	
	/**
	* @brief Renders the game canvas and UI elements
	* 
	* Draws ship (with flashing during invincibility), thrust indicator,
	* asteroids, missiles, aiming reticle, score, lives, counts, time,
	* FPS, and game over message
	* @return void
	*/
	void draw();

protected:
	double start_tic; ///< Starting tick count for timing
	double freq; ///< Tick frequency for time calculations
	int frame = 0; ///< Current frame count
	double elapsed_time; ///< Elapsed time since game start in seconds
	float FPS; ///< Frames per second calculation

	cv::Point2f _joystick; ///< Joystick position from microcontroller (x, y)
	cv::Point2f _facing_direction; ///< Ship's facing direction based on joystick input
	bool _button_A; ///< Button A state (reset game)
	bool _button_B; ///< Button B state (fire missile)

	CShip _ship; ///< The player's ship
	CAstroid _astroid; ///< Unused single asteroid (kept for compatibility)
	std::vector<CAstroid> _astroids; ///< List of active asteroids in the game
	std::vector<CMissile> _missiles; ///< List of active missiles fired by the ship

private:
	int _score = 0; ///< Current player score (10 points per asteroid destroyed)

	int _invincibility_timer = 0; ///< Frames remaining of invincibility after hit (45 frames = ~0.8 seconds)
	
	/**
	* @brief Resets the game to initial state
	* 
	* Respawns ship at center, clears and regenerates 10 asteroids,
	* clears all missiles, resets score, timers, and frame counter
	* @return void
	*/
	void reset_game();

	int _asteroid_spawn_timer = 0; ///< Frame counter for timed asteroid spawning
	const int ASTEROID_SPAWN_INTERVAL = 100; ///< Frames between automatic asteroid spawns (~1.8 seconds)
};
