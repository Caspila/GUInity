#include "Time.hpp"

/** Time that the timer started. Used by FPS. */
std::chrono::steady_clock::time_point Time::startTimer = std::chrono::high_resolution_clock::now();
/** Time that the timer ended. Used by FPS. */
std::chrono::steady_clock::time_point Time::endTimer = std::chrono::high_resolution_clock::now();

/** Time that the stopwatch started. Generic use. */
std::chrono::steady_clock::time_point Time::stopwatchTimerStart = std::chrono::high_resolution_clock::now();
/** Time that the stopwatch stopped. Generic use. */
std::chrono::steady_clock::time_point Time::stopwatchTimerEnd = std::chrono::high_resolution_clock::now();

/** The duration of the last frame */
float Time::deltaTime = 0.0f;
/** The index of the last frame that was added to the window */

int Time::frameIndex = 0;
/** The current sum of all the frames in the window */

float Time::frameSum = 0.0f;

/** The circular window of frame duration. Used to calculate smooth FPS */

float Time::FPSWindow[FPS_WINDOW_SIZE];


/** Initializes frame timer */
void Time::frameStart()
{
	startTimer = std::chrono::high_resolution_clock::now();
}
/** Stops frame timer
 @return frame duration
 */
float Time::frameEnd()
{
	endTimer = std::chrono::high_resolution_clock::now();
	
	auto deltaTime2 = endTimer - startTimer;
	
    
	deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime2).count() * 0.001f;
    
    return getAvgFPS(deltaTime);
}

/** Add a new frame duration to the window and get the average FPS */
float Time::getAvgFPS(float deltaTime)
{
    frameSum -= FPSWindow[frameIndex];
    frameSum += deltaTime;
    FPSWindow[frameIndex] = deltaTime;
    
    if(++frameIndex==FPS_WINDOW_SIZE)
        frameIndex = 0;
    
    return frameSum/FPS_WINDOW_SIZE;
}

/** Initializes stopwatch */
void Time::stopwatchStart()
{
	stopwatchTimerStart = std::chrono::high_resolution_clock::now();
}

/** Stops stopwatch
 @return stopwatch duration
 */
float Time::stopwatchEnd()
{
	stopwatchTimerEnd = std::chrono::high_resolution_clock::now();
	
	auto deltaTime2 = stopwatchTimerEnd - stopwatchTimerStart;
	
	return std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime2).count() * 0.001f;
}