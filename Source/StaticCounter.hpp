#pragma once

// found this at http://stackoverflow.com/questions/1390913/are-static-variables-in-a-base-class-shared-by-all-derived-classes
// Explanation http://en.wikipedia.org/wiki/Curiously_recurring_template_pattern

template <typename T>
class StaticCounter
{
public:
	static int nCount;
};


template <typename T> int StaticCounter<T>::nCount(0);