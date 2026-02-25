#pragma once
#include "CGameObject.h"

class CAstroid : public CGameObject
{
	public:
	CAstroid();
	CAstroid(int _size, cv::Point2f _intitalPosition, cv::Point2f _initialVelocity);
	~CAstroid();

protected:
	int _size;
	cv::Point2i _initialPosition;
	cv::Point2i _initialVelocity;
};
