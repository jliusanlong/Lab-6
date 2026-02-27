#pragma once
#include <opencv2/core.hpp>

/**
* @brief Base class for all game objects in the Asteroids game
*
* This class provides common functionality for game entities including
* position, velocity, acceleration, collision detection, rendering,
* and physics simulation with drag and thrust.
*
* @author Johnny Liu
*/
class CGameObject 
{
public:
	/**
	* @brief Updates object position based on physics
	* 
	* Applies acceleration to velocity, caps velocity to max_speed,
	* then updates position. Called every frame.
	* @return void
	*/
	void move();
	
	/**
	* @brief Gets the current position of the object
	* 
	* @return cv::Point2f The current (x, y) position
	*/
	cv::Point2f get_pos();

	/**
	* @brief Checks collision with another game object
	* 
	* Uses circular collision detection based on distance between
	* centers and sum of radii.
	* 
	* @param obj Reference to another CGameObject to check collision with
	* @return bool True if objects are colliding, false otherwise
	*/
	bool collide(CGameObject &obj);
	
	/**
	* @brief Checks if object has collided with board boundaries
	* 
	* @param board The size of the game board (width, height)
	* @return bool True if object touches any wall, false otherwise
	*/
	bool collide_wall(cv::Size board);
	
	/**
	* @brief Wraps object position around screen edges
	* 
	* When object exits one side of the screen, it reappears on
	* the opposite side (classic Asteroids behavior).
	* 
	* @param board The size of the game board (width, height)
	* @return void
	*/
	void wrap_wall(cv::Size board);

	/**
	* @brief Decreases object's life count by 1
	* 
	* Called when object takes damage
	* @return void
	*/
	void hit();
	
	/**
	* @brief Gets the current number of lives
	* 
	* @return int Number of lives remaining
	*/
	int get_lives();

	/**
	* @brief Sets the velocity vector directly
	* 
	* Used primarily for missiles to set initial velocity
	* 
	* @param vel The velocity vector (x, y)
	* @return void
	*/
	void set_velocity(cv::Point2f vel);
	
	/**
	* @brief Updates object based on joystick input
	* 
	* Converts joystick position to thrust direction and
	* applies physics for ship movement.
	* 
	* @param pos Joystick position from microcontroller
	* @return void
	*/
	void set_pos(cv::Point2f pos);
	
	/**
	* @brief Sets position directly without physics
	* 
	* Used for initializing missile position at ship location
	* 
	* @param pos The (x, y) position to set
	* @return void
	*/
	void set_missile_pos(cv::Point2f pos);

	/**
	* @brief Applies thrust acceleration based on input direction
	* 
	* Normalizes input direction, sets facing direction, and applies
	* acceleration in that direction. Sets thrusting flag.
	* 
	* @param direction The direction vector to thrust toward
	* @return void
	*/
	void apply_thrust(cv::Point2f direction);
	
	/**
	* @brief Applies drag to slow down the object
	* 
	* Multiplies velocity by drag coefficient each frame to simulate
	* friction. Stops movement when velocity becomes very small.
	* @return void
	*/
	void apply_drag();
	
	/**
	* @brief Checks if object is currently thrusting
	* 
	* @return bool True if thrust is active, false otherwise
	*/
	bool is_thrusting() const;
	
	/**
	* @brief Gets the normalized facing direction vector
	* 
	* @return cv::Point2f Unit vector indicating facing direction
	*/
	cv::Point2f get_direction();

	/**
	* @brief Draws the object on the canvas
	* 
	* Renders the object as a circle with specified color and radius
	* 
	* @param im Reference to the canvas Mat to draw on
	* @return void
	*/
	void draw(cv::Mat& im);

protected:
	cv::Point2f _position; ///< Current (x, y) position of the object
	cv::Point2f _facing_direction; ///< Unit vector indicating facing direction
	cv::Scalar _color = { 255,255,255 }; ///< RGB color for rendering (default white)

	cv::Point2f _velocity; ///< Current velocity vector (x, y)
	cv::Point2f _acceleration; ///< Current acceleration vector (x, y)
	float _drag = 0.98f; ///< Drag coefficient (0.98 = 2% velocity loss per frame)

	int _radius; ///< Radius of the object in pixels for collision and rendering
	int _lives; ///< Number of lives or hits remaining

	bool _thrusting = false; ///< True when thrust is being applied (for visual effects)
};
