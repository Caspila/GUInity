#include "CapsuleCollider.hpp"
#include "Physics.hpp"
#include "Math.hpp"

CapsuleCollider::CapsuleCollider()
{
}


CapsuleCollider::~CapsuleCollider()
{
}


void CapsuleCollider::init()
{

	shape = Physics::createCapsuleCollider(getActor());
	//setOrientation(RotateAxis::x);
}

void CapsuleCollider::setOrientation(RotateAxis orientation)
{
	PxTransform transform = shape->getLocalPose();
	switch (orientation)
	{
	case x:
		shape->setLocalPose(PxTransform(transform.p, PxQuat::createIdentity()));
		break;
	case z:
		shape->setLocalPose(PxTransform(transform.p, PxQuat(Math::Deg2Radian * 90, PxVec3(0,1,0))));
		break;
	case y:
		shape->setLocalPose(PxTransform(transform.p, PxQuat(Math::Deg2Radian * 90, PxVec3(0, 0, 1))));
		break;
	default:
		break;
	}
}

void CapsuleCollider::setHeight(float height)
{
	PxCapsuleGeometry geometry;
	shape->getCapsuleGeometry(geometry);

	geometry.halfHeight = height;

	shape->setGeometry(geometry);

}

void CapsuleCollider::setRadius(float radius)
{

	PxCapsuleGeometry geometry;
	shape->getCapsuleGeometry(geometry);

	geometry.radius = radius;

	shape->setGeometry(geometry);
}