#pragma once

#include "CBase4618.h"
#include "CShip.h"
#include "CAstroid.h"
#include "CMissile.h"
#include <vector>

class CAstroidGame : public CBase4618
{
public:
	CAstroidGame(int comport, int rows, int cols);
	~CAstroidGame();
	void run();
	void gpio();
	void update();
	void draw();


protected:
	double start_tic; ///< Starting tick count for timing
	double freq; ///< Tick frequency for time calculations
	int frame = 0; ///< Current frame count
	double elapsed_time; ///< Elapsed time since start
	float FPS; ///< Frames per second calculation

	cv::Point2f _joystick; ///< Joystick position from microcontroller
	cv::Point2f _facing_direction; ///< Ship's facing direction based on joystick input
	bool _button_A; ///< Button A state from microcontroller
	bool _button_B; ///< Button B state from microcontroller

	CShip _ship;
	CAstroid _astroid;
	std::vector<CAstroid> _astroids; ///< List of astroids in the game
	std::vector<CMissile> _missiles; ///< List of missiles fired by the ship
};
