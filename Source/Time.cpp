#include "Time.hpp"

std::chrono::steady_clock::time_point Time::startTimer = std::chrono::high_resolution_clock::now();
std::chrono::steady_clock::time_point Time::endTimer = std::chrono::high_resolution_clock::now();

float Time::deltaTime = 0.0f;

Time::Time()
{
}


Time::~Time()
{
}

void Time::frameStart()
{
	startTimer = std::chrono::high_resolution_clock::now();
}
void Time::frameEnd()
{
	endTimer = std::chrono::high_resolution_clock::now();
	
	auto deltaTime2 = endTimer - startTimer;
	
	deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime2).count() * 0.001f;
}