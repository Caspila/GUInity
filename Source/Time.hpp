#pragma once

#include <chrono>

class Time
{
	
public:
	Time();
	~Time();

	static std::chrono::steady_clock::time_point startTimer;
	static std::chrono::steady_clock::time_point endTimer;

	static void frameStart();
	static void frameEnd();
	
	static float deltaTime;


};

