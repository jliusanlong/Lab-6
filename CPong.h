#pragma once

#include "CBase4618.h"	

/**
* @brief Implements a Pong game application
*
* This class creates an interactive Pong game using joystick input for paddle control,
* ball physics, collision detection, and score tracking.
*
* @author Johnny Liu
*/
class CPong : public CBase4618
{
public:
	/**
	* @brief Constructor for CPong
	* 
	* @param comport The COM port number for microcontroller communication
	* @param rows The number of rows for the canvas
	* @param cols The number of columns for the canvas
	*/
	CPong(int comport, int rows, int cols);

	/**
	* @brief Destructor for CPong
	*/
	~CPong();

	/**
	* @brief Main application loop
	* 
	* Runs the continuous loop for the Pong game,
	* handling input, updates, and rendering
	* @return void
	*/
	void run();

	/**
	* @brief Reads GPIO inputs from the microcontroller
	* 
	* Retrieves joystick position and button states
	* @return void
	*/
	void gpio();

	/**
	* @brief Updates game state
	* 
	* Processes paddle movement, ball physics, collision detection,
	* and score tracking
	* @return void
	*/
	void update();

	/**
	* @brief Renders the game canvas and UI elements
	* 
	* Draws paddles, ball, score, GUI controls, and displays the window
	* @return void
	*/
	void draw();

private:
	int frame = 0; ///< Current frame count
	float FPS; ///< Frames per second calculation

	int _compScore = 0; ///< Computer paddle score
	int _playerScore = 0; ///< Player paddle score

	cv::Point2f _ballPos = { 500, 375 }; ///< Current ball position (x, y)
	cv::Point2f _ballVel = { 0.05, 0.05 }; ///< Ball velocity vector (x, y)

	double start_tic; ///< Starting tick count for timing
	double freq; ///< Tick frequency for time calculations
	double elapsed_time; ///< Total elapsed time since start
	double time_now; ///< Current time

	bool _button_A; ///< State of button A
	bool _bounce = false; ///< Ball bounce flag
	
	int _paddleHeight = 220; ///< Height of paddles in pixels

	cv::Point2f _compPaddleTL = { 0, 265 }; ///< Computer paddle top-left corner
	cv::Point2f _compPaddleBR = { 20, 485 }; ///< Computer paddle bottom-right corner
	cv::Point2f _playerPaddleTL = { 980, 265 }; ///< Player paddle top-left corner
	cv::Point2f _playerPaddleBR = { 1000, 485 }; ///< Player paddle bottom-right corner

	float _ballSize = 25; ///< Radius of the ball in pixels
	float _velocity = 100; ///< Ball velocity magnitude
	float _joystick; ///< Current joystick input value
	float _prevJoyPos; ///< Previous joystick position
	float _joyPos; ///< Current joystick position

	bool _exit_clicked = false; ///< Exit button state flag
	bool _reset = false; ///< Reset button state flag
};