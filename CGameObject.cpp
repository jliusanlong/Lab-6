#include "stdafx.h"
#include "CGameObject.h"


void CGameObject::set_pos(cv::Point2f pos) 
{ 
	pos.x -= 50;
	pos.y -= 50;
	pos.y *= -1;


	// Apply thrust based on joystick input
	apply_thrust(pos);

	/*
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
	*/
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
	// Update velocity based on acceleration
	_velocity += _acceleration;

	// Cap maximum velocity
	float max_speed = 10.0f;
	float speed = sqrt(_velocity.x * _velocity.x + _velocity.y * _velocity.y);
	if (speed > max_speed)
	{
		_velocity = (_velocity / speed) * max_speed;
	}

	// Update position based on velocity
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

void CGameObject::apply_thrust(cv::Point2f direction)
{
	float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);

	if (magnitude > 2.0f)  // Only apply thrust if joystick moved significantly
	{
		_thrusting = true;
		_facing_direction = cv::Point2f(direction.x / magnitude, direction.y / magnitude);

		// Apply acceleration in the direction of thrust
		float thrust_power = 0.5f;  // Adjust this value to control acceleration
		_acceleration = _facing_direction * thrust_power;
	}
	else
	{
		_thrusting = false;
		_acceleration = cv::Point2f(0, 0);
	}
}

void CGameObject::apply_drag()
{
	// Apply drag to slow down the ship
	_velocity *= _drag;

	// Stop completely if velocity is very small
	if (abs(_velocity.x) < 0.1f) _velocity.x = 0;
	if (abs(_velocity.y) < 0.1f) _velocity.y = 0;
}

bool CGameObject::is_thrusting() const
{
	return _thrusting;
}