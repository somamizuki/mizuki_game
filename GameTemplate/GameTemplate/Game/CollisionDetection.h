#pragma once
#include "Physics/CapsuleCollider.h"
#include "Physics/RigidBody.h"
class CollisionDetection
{
	/// <summary>
	/// ���ς̌��ʂ�1.0�`-1.0�͈̔͂𒴂��Ȃ��悤�ɂ���B
	/// </summary>
	/// <param name="dotresult">���ό���(float)</param>
	/// <returns>�p�x���W�A��(float)</returns>
	float Acos(float cosTheta)
	{
		float resulte = acosf(min(1.0f, max(-1.0f, cosTheta)));
		return resulte;
	}
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CollisionDetection();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CollisionDetection();
	/// <summary>
	/// ���������H
	/// </summary>
	/// <param name="oldbonepos">�O�t���[���̃{�[���̃|�W�V����(CVector3)</param>
	/// <param name="nowbonepos">���݂̃{�[���̃|�W�V����(CVector3)</param>
	/// <param name="radius">���a(float)</param>
	/// <returns>bool</returns>
	bool IsHIT(CVector3 oldbonepos, CVector3 nowbonepos, float radius);
	
};

