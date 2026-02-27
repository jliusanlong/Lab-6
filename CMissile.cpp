#include "stdafx.h"
#include "CMissile.h"

CMissile::CMissile()
{
	_radius = 5;
	_lives = 1;
	
}

CMissile::~CMissile()
{
}

void CMissile::move()
{
	// Missiles move without speed cap or acceleration
	_position += _velocity;
}