#pragma once

#include <chrono>


class Time
{
	
public:
	Time();
	~Time();

	static std::chrono::steady_clock::time_point startTimer;
	static std::chrono::steady_clock::time_point endTimer;

    static std::chrono::steady_clock::time_point stopwatchTimerStart;
	static std::chrono::steady_clock::time_point stopwatchTimerEnd;
    
    static int const FPS_WINDOW_SIZE = 100;
    
    static float FPSWindow[FPS_WINDOW_SIZE];
    
	static void frameStart();
	static float frameEnd();
    
    static void stopwatchStart();
    static float stopwatchEnd();

	static float deltaTime;
    
private:

    static float frameSum;
    static int frameIndex;


    static float getAvgFPS(float deltaTime);
};

