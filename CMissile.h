#pragma once

#include "CGameObject.h"

class CMissile : public CGameObject
{
	public:
	CMissile();
	~CMissile();
	void move();  // Override move method
};