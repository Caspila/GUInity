#pragma once

// found this at http://stackoverflow.com/questions/1390913/are-static-variables-in-a-base-class-shared-by-all-derived-classes
// Explanation http://en.wikipedia.org/wiki/Curiously_recurring_template_pattern

/** Used for debugging to know if memory is being released properly by counting the instances of each class that inherits from this */
template <typename T>
class StaticCounter
{
public:
	static int nCount;
};


template <typename T> int StaticCounter<T>::nCount(0);