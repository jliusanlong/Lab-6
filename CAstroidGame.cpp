#include "stdafx.h"
#include "CAstroidGame.h"
#include "cvui.h"




CAstroidGame::CAstroidGame(int comport, int rows, int cols)
{
	_control.init_com(comport);
	_canvas = cv::Mat::zeros(rows, cols, CV_8UC3);

	cvui::init("AstroidGame");

	freq = cv::getTickFrequency(); // Get tick frequency

	start_tic = cv::getTickCount();	// Get number of ticks since event (such as computer on)

	srand((unsigned int)time(0));



	_ship = CShip(20, 10);

	for (int i = 0; i < 10; i++)
	{
		CAstroid astroid;
		astroid.ensure_safe_spawn(_ship.get_pos(), 150.0f);
		_astroids.push_back(CAstroid());
	}
	

}

CAstroidGame::~CAstroidGame()
{
}

void CAstroidGame::gpio()
{
	_joystick.x = _control.get_analog(1, 2);
	_joystick.y = _control.get_analog(1, 26);


	_button_A = _control.get_button(33);
	_button_B = _control.get_button(32);

}

void CAstroidGame::update()
{
	auto end_time = std::chrono::system_clock::now() + std::chrono::milliseconds(18);
	////////////////////////

	_ship.set_pos(_joystick);




	_ship.wrap_wall(cv::Size(1000, 750));

	for (auto& astroid : _astroids)
	{
		astroid.move();
		astroid.get_pos();
		astroid.wrap_wall(cv::Size(1000, 750));
	}

	// Decrease invincibility timer
	if (_invincibility_timer > 0)
	{
		_invincibility_timer--;
	}

	// Check collisions between ship and asteroids (only if not invincible)
	if (_invincibility_timer == 0)
	{
		// Check collisions between ship and asteroids
		for (auto astroid_it = _astroids.begin(); astroid_it != _astroids.end(); )
		{
			if (_ship.collide(*astroid_it))
			{
				_ship.hit();
				_invincibility_timer = 45;
				astroid_it = _astroids.erase(astroid_it);

				// Spawn new asteroid safely
				CAstroid new_astroid;
				new_astroid.ensure_safe_spawn(_ship.get_pos(), 150.0f);
				_astroids.push_back(new_astroid);
				break;
			}
			else
			{
				++astroid_it;
			}
		}
	}
	// Check for reset button
	if (_button_A == true)
	{
		reset_game();
	}


	if (_button_B == true)
	{
		_missiles.push_back(CMissile());
		_missiles.back().set_missile_pos(_ship.get_pos());
		_missiles.back().set_velocity (_ship.get_direction() * 10.0f);
	}
	for (auto& missile : _missiles)
	{
		missile.move();

	}

	// Check collisions between missiles and asteroids
	for (auto missile_it = _missiles.begin(); missile_it != _missiles.end(); )
	{
		bool missile_hit = false;

		for (auto astroid_it = _astroids.begin(); astroid_it != _astroids.end(); )
		{
			if (missile_it->collide(*astroid_it))
			{
				// Collision detected!
				_score += 10;
				astroid_it = _astroids.erase(astroid_it);  // Remove asteroid

				// Spawn new asteroid safely
				CAstroid new_astroid;
				new_astroid.ensure_safe_spawn(_ship.get_pos(), 150.0f);
				_astroids.push_back(new_astroid);

				missile_hit = true;
				break;  // Missile can only hit one asteroid
			}
			else
			{
				++astroid_it;
			}
		}

		if (missile_hit)
		{
			missile_it = _missiles.erase(missile_it);  // Remove missile
		}
		else
		{
			++missile_it;
		}
	}

	//Chat
	// Remove missiles that collided with walls
	_missiles.erase
	(
		std::remove_if(_missiles.begin(), _missiles.end(),
		[](CMissile& m) { return m.collide_wall(cv::Size(1000, 750)); }),
		_missiles.end()
	);



	



    ////// Sleep if time remaining//////////
	std::this_thread::sleep_until(end_time);


	elapsed_time = (cv::getTickCount() - start_tic) / freq;
	frame++;

	FPS = frame / elapsed_time;
}

void CAstroidGame::draw()
{
	_canvas.setTo(cv::Scalar(0, 0, 0));


	//_ship.draw(_canvas);

	// Draw ship with flashing effect when invincible
// Flash every 5 frames (creates visible blinking effect)
	if (_invincibility_timer == 0 || (_invincibility_timer / 3) % 2 == 0)
	{
		_ship.draw(_canvas);
	}

	for (auto& astroid : _astroids)
	{
		astroid.draw(_canvas);
	}

	for (auto& missile : _missiles)
	{
		missile.draw(_canvas);
	}

	// Draw indicator showing where ship is facing
	cv::Point2f ship_pos = _ship.get_pos();
	cv::Point2f facing = _ship.get_direction();
	cv::Point2f aim_point = ship_pos + (facing * 40.0f);  // 40 pixels ahead
	cv::circle(_canvas, aim_point, 5, cv::Scalar(0, 255, 0), -1);  // Green dot
	cv::line(_canvas, ship_pos, aim_point, cv::Scalar(0, 255, 0), 2);



	cvui::printf(_canvas, 400, 20, "Score = %d", _score);

	cvui::printf(_canvas, 500, 20, "Lives = %d", _ship.get_lives());

	cvui::printf(_canvas, 40, 20, "Asteroids = %d", (int)_astroids.size());

	cvui::printf(_canvas, 200, 20, "Missiles = %d", (int)_missiles.size());

	cvui::printf(_canvas, 750, 20, "Elapsed Time = %.2f", elapsed_time);

	cvui::printf(_canvas, 900, 20, "FPS = %.2f", FPS);

	if (_ship.get_lives() <= 0)
	{
		// Game over logic
		cvui::printf(_canvas, 400, 375, 0.8, 0xFF0000, "GAME OVER!");
	}


	cvui::update();

	cv::imshow("AstroidGame", _canvas);
}

void CAstroidGame::run()
{
	while(true)
	{
		CAstroidGame::gpio();
		CAstroidGame::update();
		CAstroidGame::draw();

		int key = cv::waitKey(1) & 0xFF;
		if (key == 'q' || key == 'Q')
		{
			cv::destroyWindow("AstroidGame");
			break;
		}
	}
}

void CAstroidGame::reset_game()
{
	// Reset ship
	_ship = CShip(20, 10);

	// Clear and respawn asteroids
	_astroids.clear();
	for (int i = 0; i < 10; i++)
	{
		CAstroid astroid;
		astroid.ensure_safe_spawn(_ship.get_pos(), 150.0f);
		_astroids.push_back(astroid);
	}

	// Clear missiles
	_missiles.clear();

	// Reset game state
	_score = 0;
	_invincibility_timer = 0;

	// Reset timer
	start_tic = cv::getTickCount();
	frame = 0;
}