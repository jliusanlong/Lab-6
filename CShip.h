#pragma once
#include "CGameObject.h"

class CShip : public CGameObject
{
public:
	CShip();
	CShip(int _size, int _lives);
	~CShip();


};