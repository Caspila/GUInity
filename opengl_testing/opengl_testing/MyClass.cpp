#include "MyClass.h"


MyClass::MyClass()
{
}


MyClass::~MyClass()
{
}

MyClass::MyClass(MyClass&& myClass)
{
	value = myClass.value;
	myClass.value = nullptr;
}