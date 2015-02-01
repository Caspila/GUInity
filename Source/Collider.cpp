#include "Collider.hpp"

/** Component setActive override */
void Collider::setActive(bool isActive)
{
	shape->setFlag(PxShapeFlag::eVISUALIZATION, isActive);
}

/** Is this collider a trigger or should it simulate real world physics? */
void Collider::setTrigger(bool isTrigger)
{
	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, !isTrigger);
	shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, isTrigger);
}
/** isTrigger getter*/
bool Collider::getIsTrigger()
{
	return shape->getFlags() & PxShapeFlag::eTRIGGER_SHAPE;
}

/** Is this collider used for queries only? */
void Collider::setQueryOnly(bool queryOnly)
{
	shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, queryOnly);
}
/** queryOnly getter*/
bool Collider::getQueryOnly()
{
	return shape->getFlags() & PxShapeFlag::eSCENE_QUERY_SHAPE;
}


