#pragma once

#include <chrono>

/** Helper class to handle time */
class Time
{
private:
    
    /** Time that the timer started. Used by FPS. */
    static std::chrono::steady_clock::time_point startTimer;
    /** Time that the timer ended. Used by FPS. */
	static std::chrono::steady_clock::time_point endTimer;
    
    /** Time that the stopwatch started. Generic use. */
    static std::chrono::steady_clock::time_point stopwatchTimerStart;
    /** Time that the stopwatch stopped. Generic use. */
	static std::chrono::steady_clock::time_point stopwatchTimerEnd;
    
    /** The size of the circular window of frame duration. */
    static int const FPS_WINDOW_SIZE = 100;
    /** The circular window of frame duration. Used to calculate smooth FPS */
    static float FPSWindow[FPS_WINDOW_SIZE];
    
    /** The current sum of all the frames in the window */
    static float frameSum;
    /** The index of the last frame that was added to the window */
    static int frameIndex;
    
    /** Add a new frame duration to the window and get the average FPS */
    static float getAvgFPS(float deltaTime);
	
public:
    
    
    /** Initializes frame timer */
	static void frameStart();
    /** Stops frame timer
     @return frame duration
     */
	static float frameEnd();
    
    /** Initializes stopwatch */
    static void stopwatchStart();
    /** Stops stopwatch
     @return stopwatch duration
     */
    static float stopwatchEnd();
    
    /** The duration of the last frame */
	static float deltaTime;
    
    
};

