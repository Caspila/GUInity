#pragma once


class MyClass
{
public:


	MyClass();
	~MyClass();


	MyClass(MyClass&& myClass);

	int *value;

};

