#pragma once
#include "Physics/CapsuleCollider.h"
#include "Physics/RigidBody.h"
class HitObject
{
public:
	HitObject();
	~HitObject();
	void Init(CVector3& position, CQuaternion rotation, float radius,float height);			//������
	const CVector3& Execute(float deltaTime, CVector3& moveSpeed, CQuaternion& rotation);
	RigidBody* GetRigidBody()
	{
		return &m_rigidBody;
	}
	void RemoveRigidBoby();
private:
	RigidBody m_rigidBody;
	CapsuleCollider m_collider;						//�R���C�_�[�B
	CVector3 m_position = CVector3::Zero();	//���W�B
	float m_radius = 0.0f;
	float m_height = 0.0f;
};

