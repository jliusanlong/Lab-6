#pragma once
#include "CGameObject.h"

class CAstroid : public CGameObject
{
	public:
	CAstroid();
	CAstroid(int _size, cv::Point2f _intitalPosition, cv::Point2f _initialVelocity);
	~CAstroid();

	void ensure_safe_spawn(cv::Point2f ship_pos, float min_distance);

protected:
	int _size;
	cv::Point2i _initialPosition;
	cv::Point2i _initialVelocity;
};
