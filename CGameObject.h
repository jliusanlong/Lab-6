#pragma once
#include <opencv2/core.hpp>



class CGameObject 
{
public:
	void move();
	cv::Point2f get_pos();


	bool collide(CGameObject &obj);
	bool collide_wall(cv::Size board);
	void wrap_wall(cv::Size board);


	void hit();
	int get_lives();


	void set_velocity(cv::Point2f vel);
	void set_pos(cv::Point2f pos);
	void set_missile_pos(cv::Point2f pos);

	void apply_thrust(cv::Point2f direction);
	void apply_drag();
	bool is_thrusting() const;

	
	cv::Point2f get_direction();
	
	

	void draw(cv::Mat& im);
protected:

	cv::Point2f _position;
	cv::Point2f _facing_direction;
	cv::Scalar _color = { 255,255,255 };

	cv::Point2f _velocity;

	cv::Point2f _acceleration;  // Add this
	float _drag = 0.98f;  // Add this - friction/drag coefficient

	int _radius;
	int _lives;

	bool _thrusting = false;  // Add this - track if thrust is acti



};
