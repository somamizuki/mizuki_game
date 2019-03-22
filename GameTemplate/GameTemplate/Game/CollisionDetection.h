#pragma once
#include "Physics/CapsuleCollider.h"
#include "Physics/RigidBody.h"
class CollisionDetection
{
	float Acos(float cosTheta)
	{
		float resulte = acosf(min(1.0f, max(-1.0f, cosTheta)));
		return resulte;
	}
public:
	CollisionDetection();
	~CollisionDetection();
	bool IsHIT(CVector3 oldbonepos, CVector3 nowbonepos, float radius);
	
};

