#include "stdafx.h"
#include "CAstroid.h"



CAstroid::CAstroid()
{
	_size = 10 + rand() % 71;
	_radius = _size;

	_initialPosition.x = rand() % 1000;
	_position.x = _initialPosition.x;

	_initialPosition.y = rand() % 750;
	_position.y = _initialPosition.y;

	_color = cv::Scalar( rand() % 256, rand() % 256, rand() % 256 );


	_initialVelocity.x = -5 + rand() % 11;
	_velocity.x = _initialVelocity.x;

	_initialVelocity.y = -5 + rand() % 11;
	_velocity.y = _initialVelocity.y;


}

CAstroid::~CAstroid()
{
}