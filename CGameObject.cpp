#include "stdafx.h"
#include "CGameObject.h"


void CGameObject::set_pos(cv::Point2f pos) 
{ 
	pos.x -= 50;
	pos.y -= 50;
	pos.y *= -1;

	float magnitude = sqrt(pos.x * pos.x + pos.y * pos.y);

	//Stabalize at origin
	if (pos.x > 2 || pos.x < -2)
	{
		_facing_direction.x = pos.x / magnitude;
		_position.x += pos.x / 5;
	}

	if (pos.y > 2 || pos.y < -2)
	{
		_facing_direction.y = pos.y / magnitude;
		_position.y += pos.y / 5;
	}	
}

cv::Point2f CGameObject::get_direction()
{
	return _facing_direction;
}

void CGameObject::set_missile_pos(cv::Point2f pos)
{
	_position.x = pos.x;
	_position.y = pos.y;
}

void CGameObject::draw(cv::Mat& im)
{
	// Draw the game object as a circle
	cv::circle(im, _position, _radius, _color, 2);
}

void CGameObject::move()
{
	// Update the position based on velocity
	_position += _velocity;
}

cv::Point2f CGameObject::get_pos()
{
	return cv::Point2f(_position.x, _position.y);
}

bool CGameObject::collide_wall(cv::Size board)
{

	if (_position.x - _radius <= 0) return true;              // left
	if (_position.x + _radius >= board.width) return true;    // right
	if (_position.y - _radius <= 0) return true;              // top
	if (_position.y + _radius >= board.height) return true;   // bottom

	return false;
}

void CGameObject::wrap_wall(cv::Size board)
{
	if (_position.x < -_radius) _position.x = (float)(board.width + _radius);
	if (_position.x > board.width + _radius) _position.x = (float)(-_radius);

	if (_position.y < -_radius) _position.y = (float)(board.height + _radius);
	if (_position.y > board.height + _radius) _position.y = (float)(-_radius);
}

void CGameObject::set_velocity(cv::Point2f vel)
{
	_velocity = vel;
}

bool CGameObject::collide(CGameObject& obj)
{
	// Calculate distance between two objects
	cv::Point2f diff = _position - obj._position;
	float distance = sqrt(diff.x * diff.x + diff.y * diff.y);

	// Check if distance is less than sum of radii
	return distance < (_radius + obj._radius);
}

void CGameObject::hit()
{
	_lives--;
}

int CGameObject::get_lives()
{
	return _lives;
}

