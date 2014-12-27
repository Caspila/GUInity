#pragma once

template <typename T>
class PointerHolder
{
public:
	PointerHolder(T* pointer)
	{
		this->pointer = pointer;
	}
	~PointerHolder() {};

	T* pointer;
};

