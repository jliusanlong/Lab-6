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

	for (int i = 0; i < 5; i++)
	{
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
	_facing_direction = _ship.get_direction(_joystick);
	_ship.wrap_wall(cv::Size(1000, 750));

	for (auto& astroid : _astroids)
	{
		astroid.move();
		astroid.get_pos();
		astroid.wrap_wall(cv::Size(1000, 750));
	}

	if (_button_B == true)
	{
		_missiles.push_back(CMissile());
		_missiles.back().set_missile_pos(_ship.get_pos());
		_missiles.back().set_velocity (cv::Point2f(1, 1));
	}
	for (auto& missile : _missiles)
	{
		missile.move();
	}



	_facing_direction = _ship.get_direction (_joystick) + _ship.get_pos();



    ////// Sleep if time remaining//////////
	std::this_thread::sleep_until(end_time);


	elapsed_time = (cv::getTickCount() - start_tic) / freq;
	frame++;

	FPS = frame / elapsed_time;
}

void CAstroidGame::draw()
{
	_canvas.setTo(cv::Scalar(0, 0, 0));


	_ship.draw(_canvas);

	for (auto& astroid : _astroids)
	{
		astroid.draw(_canvas);
	}

	for (auto& missile : _missiles)
	{
		missile.draw(_canvas);
	}

	cv::circle(_canvas, _facing_direction, 1, cv::Scalar(256,256,256), 2);




	cvui::printf(_canvas, 40, 20, "Asteroids = %d", (int)_astroids.size());

	cvui::printf(_canvas, 750, 20, "Elapsed Time = %.2f", elapsed_time);

	cvui::printf(_canvas, 900, 20, "FPS = %.2f", FPS);

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