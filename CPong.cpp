#include "stdafx.h"
#include "CPong.h"
#include "cvui.h"


CPong::CPong(int comport, int rows, int cols)
{
	_control.init_com(comport);
	_canvas = cv::Mat::zeros(rows, cols, CV_8UC3);

	cvui::init("Pong");

	freq = cv::getTickFrequency(); // Get tick frequency

	start_tic = cv::getTickCount();	// Get number of ticks since event (such as computer on)

}

CPong::~CPong()
{
}

void CPong::gpio()
{
	_joystick = _control.get_analog(1, 26);

	_button_A = _control.get_button(33);

}

void CPong::update()
{ 
	// Set update rate at 10 Hz (100 ms per loop)

	auto end_time = std::chrono::system_clock::now() + std::chrono::milliseconds(18);


	///////////////////////////////////////

	_joystick -= 50;
	_joystick *= -1;

	//Stabalize at origin
	
	if (_joystick > 2 || _joystick < -2)
	{
		_playerPaddleTL.y += _joystick / 2;
		_playerPaddleBR.y += _joystick / 2;
	}

	if ( _playerPaddleTL.y <=0)
	{
		_playerPaddleTL.y = 0;
		_playerPaddleBR.y = _playerPaddleTL.y + _paddleHeight;
	}

	if (_playerPaddleBR.y >= 750)
	{
		_playerPaddleTL.y = 530;
		_playerPaddleBR.y = 750;
	}
	////////////////////////////////////////


	
	_compPaddleTL.y = _ballPos.y-110;
	_compPaddleBR.y = _ballPos.y+110;

	if (_compPaddleTL.y <= 0)
	{
		_compPaddleTL.y = 0;
		_compPaddleBR.y = _compPaddleTL.y + _paddleHeight;
	}

	if (_compPaddleBR.y >= 750)
	{
		_compPaddleTL.y = 530;
		_compPaddleBR.y = 750;
	}
	
	
	
	
	_ballPos += (_ballVel * _velocity);
	
	if((_ballPos.y-_ballSize) <= 0) 
	{
		
		_ballPos.y = 0 + (_ballSize+1);
		_ballVel.y *= -1;
	}

	if ((_ballPos.y + _ballSize) >= 750)
	{
		
		_ballPos.y = 750 - (_ballSize+1);
		_ballVel.y *= -1;
	}


	if(((_ballPos.y> _playerPaddleTL.y) && (_ballPos.y<_playerPaddleBR.y) && ((_ballPos.x +_ballSize)>= 980))   ||
         ((_ballPos.y > _compPaddleTL.y ) && (_ballPos.y<_compPaddleBR.y) && ((_ballPos.x - _ballSize) <= 20)))
	{
		_ballVel.x *= -1;
	}

	if ((_ballPos.x + _ballSize) >= 1000)
	{
		_ballPos = { 500,375 };
		_ballVel = { 0.05,0.05 };
		_compScore++;

	}
	
	if (_compScore == 5)
	{
		_ballPos = { 500,375 };
		
	}
	if(_button_A)
	{
		_ballPos = { 500,375 };
		_ballVel = { 0.05,0.05 };
		_compScore = 0;
		_playerScore = 0;
	}
	

	

	// Sleep if time remaining
	std::this_thread::sleep_until(end_time);


	elapsed_time = (cv::getTickCount() - start_tic) / freq;
	frame++;

	FPS = frame / elapsed_time;
}

void CPong::draw()
{
	_canvas.setTo(cv::Scalar(0, 0, 0));



	cv::circle(_canvas, _ballPos, _ballSize, cv::Scalar(255, 255, 255), cv::FILLED);

	cv::rectangle(_canvas, _compPaddleTL, _compPaddleBR, cv::Scalar(255, 255, 255), cv::FILLED);
	cv::rectangle(_canvas, _playerPaddleTL, _playerPaddleBR, cv::Scalar(255, 255, 255), cv::FILLED);

	cvui::window(_canvas, 10, 10, 250, 210, "Pong");


	cvui::printf(_canvas, 20, 40, "Ballsize = %.2f", _ballSize);
	cvui::trackbar(_canvas, 20, 55, 220, &_ballSize, (float)5, (float)100);
	
	cvui::printf(_canvas, 20, 110, "Velocity = %.2f", _velocity);
	cvui::trackbar(_canvas, 20, 125, 220, &_velocity, (float)100, (float)400);

	

	


	_exit_clicked = cvui::button(_canvas, 20, 180, "EXIT");
	_reset = cvui::button(_canvas, 90, 180, "RESET");
	if (_reset)
	{
		_canvas.setTo(cv::Scalar(0, 0, 0));  // Clear the canvas
		_ballPos = { 500,375 };
		_ballVel = { 0.05,0.05 };
		_compScore = 0;
		_playerScore = 0;
	}
	
	cvui::printf(_canvas, 750, 20, "Elapsed Time = %.2f", elapsed_time);

	cvui::printf(_canvas, 900, 20, "FPS = %.2f", FPS);

	cvui::printf(_canvas, 300, 20, "Computer: %d vs Player: %d", _compScore, _playerScore);

	if(_compScore == 5)
	{
		cvui::printf(_canvas, 400, 300, "Computer Wins!");
	}
	else if (_playerScore == 5)
	{
		cvui::printf(_canvas, 400, 300, "Player Wins!");
	}






	cvui::update();

	cv::imshow("Pong", _canvas);
}

void CPong::run()
{
	while (true)
	{
		CPong::gpio();
		CPong::update();
		CPong::draw();

		int key = cv::waitKey(1) & 0xFF;
		if (key == 'q' || key == 'Q' || _exit_clicked)
		{
			cv::destroyWindow("Pong");
			break;
		}
	}
}