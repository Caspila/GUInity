#include "MyClassFactory.h"
#include <iostream>

using namespace std;

MyClassFactory::MyClassFactory()
{
}


MyClassFactory::~MyClassFactory()
{
}

MyClass MyClassFactory::CreateInstance()
{
	MyClass myClass;

	myClass.value = new int;
	*(myClass.value) = 10;

	return myClass;
}

MyClass* MyClassFactory::CreateInstancePTR()
{
	cout << "Create PTR" << endl;

	MyClass* myClass = new MyClass();

	myClass->value = new int;
	*(myClass->value) = 10;

	return myClass;
}

void MyClassFactory::ReleaseInstancePTR(MyClass* myClass)
{
	cout << "Release PTR" <<endl;

	delete myClass->value;
	delete myClass;
}

void MyClassFactory::ReleaseInstance(MyClass myClass)
{
	delete myClass.value;
}