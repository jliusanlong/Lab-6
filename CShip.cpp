#include "stdafx.h"
#include "CShip.h"

CShip::CShip()
{
	_radius = 20;
	_lives = 10;
	_position = cv::Point2f(500, 375);
}

CShip::CShip(int _size, int _lives)
{
	_radius = _size;
	_lives = _lives;
	_position = cv::Point2f(500, 375);
	_facing_direction = cv::Point2f(0, -1);
}


CShip::~CShip()
{
}