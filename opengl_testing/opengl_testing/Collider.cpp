#include "Collider.hpp"


Collider::Collider()
{
}


Collider::~Collider()
{
}

void Collider::setTrigger(bool isTrigger)
{

	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, !isTrigger);
	shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, isTrigger);

}

void Collider::setQueryOnly(bool queryOnly)
{
	shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, queryOnly);
}

//void Collider::setActive(bool isActive)
//{
//	shape->setFlag(PxShapeFlag::)
//}

void Collider::setActive(bool isActive)
{
    shape->setFlag(PxShapeFlag::eVISUALIZATION, isActive);
//    shape->set, <#bool value#>
}