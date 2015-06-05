#include "Time.hpp"

std::chrono::steady_clock::time_point Time::startTimer = std::chrono::high_resolution_clock::now();
std::chrono::steady_clock::time_point Time::endTimer = std::chrono::high_resolution_clock::now();

std::chrono::steady_clock::time_point Time::stopwatchTimerStart = std::chrono::high_resolution_clock::now();
std::chrono::steady_clock::time_point Time::stopwatchTimerEnd = std::chrono::high_resolution_clock::now();

float Time::deltaTime = 0.0f;
int Time::frameIndex = 0;
float Time::frameSum = 0.0f;

float Time::FPSWindow[FPS_WINDOW_SIZE];

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
float Time::frameEnd()
{
	endTimer = std::chrono::high_resolution_clock::now();
	
	auto deltaTime2 = endTimer - startTimer;
	
    
	deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime2).count() * 0.001f;
    
    return getAvgFPS(deltaTime);
}

float Time::getAvgFPS(float deltaTime)
{
    frameSum -= FPSWindow[frameIndex];
    frameSum += deltaTime;
    FPSWindow[frameIndex] = deltaTime;
    
    if(++frameIndex==FPS_WINDOW_SIZE)
        frameIndex = 0;
    
    return frameSum/FPS_WINDOW_SIZE;
}

void Time::stopwatchStart()
{
	stopwatchTimerStart = std::chrono::high_resolution_clock::now();
}

float Time::stopwatchEnd()
{
	stopwatchTimerEnd = std::chrono::high_resolution_clock::now();
	
	auto deltaTime2 = stopwatchTimerEnd - stopwatchTimerStart;
	
	return std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime2).count() * 0.001f;
}