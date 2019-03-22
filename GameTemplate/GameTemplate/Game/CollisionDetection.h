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
	btRigidBody*		m_rigidbody = nullptr;
public:
	CollisionDetection();
	~CollisionDetection();
	bool CleateCollider(CVector3 oldbonepos, CVector3 nowbonepos, float radius);
	
};

