//
//  ReflectionTest.h
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-06.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef opengl_testing_mag_ReflectionTest_h
#define opengl_testing_mag_ReflectionTest_h

#include <typeinfo>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "SerializationStructs.hpp"
using namespace std;

#define CREATE_MEMBERS_TABLE()\
static vector<string> members;

#define CREATE_GET_SET(x,y)\
members.push_back(##y);\
void set_##y(x value)\
{\
    y = value;\
}\
x get_##y()\
{\
    return y;\
}\

struct MemberInfo
{
public:
    string name, type;
    MemberInfo(string type, string name)//, string type)
    {
        this->name = name;
        this->type = type;
    }
};

#define MEMBER(y,x) \
{ #y, #x },

#define PROPERTY(y,x) \
y get##x()\
{\
return x;\
}\
void set##x(y value)\
{\
x = value;\
}

//{ ##x, get_type(this->x) },


#define CREATE_TABLE(x)\
static MemberInfo* getMembers()\
{\
static MemberInfo members[] = { x };\
    return members;\
}\

#define CREATE_PUBLIC_ACCESS(param)\
void setValueFor(string param, string value)\
{\
    set##param(value);\
}\
string getValueFor(string param, string value)\
{\
   return get##param();\
}

#define setMemberValue(ob,param,value)\
ob.set##param(value);

#define GET_MEMBER_VALUE(param)\
get##param();

#define SET_MEMBER_VALUE(param, value)\
set##param(value);


#define DECLARE_SERIALIZATION(className)\
public:\
shared_ptr<ComponentDescription> getComponentDescription();\
void deserialize(shared_ptr<ComponentDescription> desc);


#define DECLARE_COMPONENT_SCRIPT(className)\
class className##_COMPONENT_DESCRIPTION\
{\
public:\
    className##_COMPONENT_DESCRIPTION() {}\
    virtual ~className##_COMPONENT_DESCRIPTION() {};\
}


//#define IMPLEMENT_COMPONENT_SCRIPT(className)\
//shared_ptr<ComponentDescription> className##_COMPONENT_DESCRIPTION::getComponentDescription()\
//{\
//    return nullptr;\
//}\
//void className##_COMPONENT_DESCRIPTION::deserialize(shared_ptr<ComponentDescription> desc)\
//{\
//}

//DECLARE_COMPONENT_SCRIPT(Test);

#define DECLARE_SUB_CLASS(sub_class_name, base_class_name) \
class sub_class_name##_ASD:base_class_name \
{ \
public: \
virtual int initialize(const void *); \
virtual int run(const void *); \
virtual void reset(); \
virtual int output(const char*); \
virtual void terminate(); \
};

//class nope_COMPONENTDESCRIPTION;

//class bla_COMPONENTDESCRIPTION
//{
//    nope_COMPONENTDESCRIPTION a;

//    className_COMPONENTDESCRIPTION a;
//};



class Person
{
 
public:
//    Test_COMPONENT_DESCRIPTION a;
    
//    nopeCOMPONENTDESCRIPTION a;
    
    string name;
    int age;
    
    PROPERTY(string,name)
    PROPERTY( int,age)
            
    CREATE_TABLE( MEMBER(string,name) MEMBER( int,age))
    
    //CREATE_PUBLIC_ACCESS()

};






#endif
