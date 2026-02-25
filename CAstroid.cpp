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

void CAstroid::ensure_safe_spawn(cv::Point2f ship_pos, float min_distance)
{
	// Regenerate position until it's far enough from ship
	int attempts = 0;
	while (attempts < 100)  // Limit attempts to prevent infinite loop
	{
		cv::Point2f diff = _position - ship_pos;
		float distance = sqrt(diff.x * diff.x + diff.y * diff.y);

		if (distance >= min_distance)
		{
			break;  // Position is safe
		}

		// Regenerate position
		_position.x = rand() % 1000;
		_position.y = rand() % 750;
		attempts++;
	}
}