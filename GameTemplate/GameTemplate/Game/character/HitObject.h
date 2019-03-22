#pragma once
#include "Physics/CapsuleCollider.h"
#include "Physics/RigidBody.h"
class HitObject
{
public:
	HitObject();
	~HitObject();
	void Init(CVector3& position, CQuaternion rotation, float radius,float height);			//初期化
	const CVector3& Execute(float deltaTime, CVector3& moveSpeed, CQuaternion& rotation);
	RigidBody* GetRigidBody()
	{
		return &m_rigidBody;
	}
	void RemoveRigidBoby();
private:
	RigidBody m_rigidBody;
	CapsuleCollider m_collider;						//コライダー。
	CVector3 m_position = CVector3::Zero();	//座標。
	float m_radius = 0.0f;
	float m_height = 0.0f;
};

