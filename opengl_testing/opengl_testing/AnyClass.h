#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class any_type
{
public:
	virtual ~any_type() {}
	virtual void print() = 0;
};

template <class T>
class concrete_type : public any_type
{
public:
	concrete_type(const T& value) : value_(value)
	{}

	virtual void print()
	{
		std::cout << value_ << '\n';
	}
private:
	T value_;
};
