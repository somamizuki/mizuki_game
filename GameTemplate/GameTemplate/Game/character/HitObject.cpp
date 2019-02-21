#include "stdafx.h"
#include "HitObject.h"
#include "Physics/CollisionAttr.h"


HitObject::HitObject()
{
}


HitObject::~HitObject()
{
	RemoveRigidBoby();
}

namespace {
	//�Փ˂����Ƃ��ɌĂ΂��֐��I�u�W�F�N�g(�Ǘp)
	struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit = false;						//�Փ˃t���O�B
		CVector3 hitPos = CVector3::Zero();		//�Փ˓_�B
		CVector3 startPos = CVector3::Zero();		//���C�̎n�_�B
		float dist = FLT_MAX;					//�Փ˓_�܂ł̋����B��ԋ߂��Փ˓_�����߂邽�߁BFLT_MAX�͒P���x�̕��������_����肤��ő�̒l�B
		CVector3 hitNormal = CVector3::Zero();	//�Փ˓_�̖@���B
		btCollisionObject* me = nullptr;		//�������g�B�������g�Ƃ̏Փ˂����O���邽�߂̃����o�B
												//�Փ˂����Ƃ��ɌĂ΂��R�[���o�b�N�֐��B
		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			if (convexResult.m_hitCollisionObject == me) {
				//�����ɏՓ˂����B
				return 0.0f;
			}
			//�Փ˓_�̖@�������������Ă���B
			CVector3 hitNormalTmp;
			hitNormalTmp.Set(convexResult.m_hitNormalLocal);
			if ( convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Ground||
				convexResult.m_hitCollisionObject->getUserIndex()== enCollisionAttr_Object) 
			{
				isHit = true;
				CVector3 hitPosTmp;
				hitPosTmp.Set(convexResult.m_hitPointLocal);
				//��_�Ƃ̋����𒲂ׂ�B
				CVector3 vDist;
				vDist.Subtract(hitPosTmp, startPos);
				float distTmp = vDist.Length();
				if (distTmp < dist) {
					//���̏Փ˓_�̕����߂��̂ŁA�ŋߖT�̏Փ˓_���X�V����B
					hitPos = hitPosTmp;
					dist = distTmp;
					hitNormal = hitNormalTmp;
				}
			}
			return 0.0f;
		}
	};
}



void HitObject::Init(CVector3& position, CQuaternion rotation, float radius, float height)
{
	m_position = position;
	//�R���W�����쐬�B
	m_radius = radius;
	m_height = height;
	m_collider.Create(radius, height);

	//���̂��������B
	RigidBodyInfo rbInfo;
	rbInfo.collider = &m_collider;
	rbInfo.mass = 0.0f;
	m_rigidBody.Create(rbInfo);
	btTransform& trans = m_rigidBody.GetBody()->getWorldTransform();
	//���̂̈ʒu���X�V�B
	trans.setOrigin(btVector3(position.x, position.y, position.z));
	trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	m_rigidBody.GetBody()->setUserIndex(enCollisionAttr_Character);
	m_rigidBody.GetBody()->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
	g_physics.AddRigidBody(m_rigidBody);
}

const CVector3& HitObject::Execute(float deltaTime, CVector3& moveSpeed, CQuaternion& rotation)
{
	//���̈ړ���ƂȂ���W���v�Z����B
	CVector3 nextPosition = m_position;
	//���x���炱�̃t���[���ł̈ړ��ʂ����߂�B�I�C���[�ϕ��B
	CVector3 addPos = moveSpeed;
	addPos *= deltaTime;
	nextPosition += addPos;
	CVector3 originalDir = addPos;
	originalDir.Normalize();

	int loopCount = 0;
	while (true) {
		//���݂̍��W���玟�̈ړ���֌������x�N�g�������߂�B
		CVector3 addPos;
		addPos.Subtract(nextPosition, m_position);
		CVector3 addPosVec = addPos;
		if (addPosVec.Length() < FLT_EPSILON) {
			//FLT_EPSILON��1���傫���A�ŏ��̒l�Ƃ̍�����\���萔�B
			//�ƂĂ��������l�̂��Ƃł��B
			break;
		}
		//�J�v�Z���R���C�_�[�̒��S���W + ����*0.1�̍��W��posTmp�ɋ��߂�B
		CVector3 posTmp = m_position;
		posTmp.y += m_height * 0.5f + m_radius + m_height * 0.1f;
		//���C���쐬�B
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		//�n�_�̓J�v�Z���R���C�_�[�̒��S���W + 0.2�̍��W��posTmp�ɋ��߂�B
		start.setOrigin(btVector3(posTmp.x, posTmp.y, posTmp.z));
		//�I�_�͎��̈ړ���BXZ���ʂł̏Փ˂𒲂ׂ�̂ŁAy��posTmp.y��ݒ肷��B
		end.setOrigin(btVector3(nextPosition.x, posTmp.y, nextPosition.z));

		SweepResultWall callback;
		callback.me = m_rigidBody.GetBody();
		callback.startPos = posTmp;
		//�Փˌ��o�B
		g_physics.ConvexSweepTest((const btConvexShape*)m_collider.GetBody(), start, end, callback);

		if (callback.isHit) {
			//���������B
			//�ǁB

			CVector3 vT0, vT1;
			//�ړ���̍��W��vT0�ɁA��_�̍��W��vT1�ɐݒ肷��B
			vT0.Set(nextPosition.x, nextPosition.y, nextPosition.z);
			vT1.Set(callback.hitPos.x, callback.hitPos.y, callback.hitPos.z);
			//�߂荞�݂��������Ă���ړ��x�N�g�������߂�B
			CVector3 vMerikomi;
			vMerikomi = vT0 - vT1;
			//�Փ˂����ǂ̖@�������߂�B�B
			CVector3 hitNormal = callback.hitNormal;
			hitNormal.Normalize();
			//�߂荞�݃x�N�g����ǂ̖@���Ɏˉe����B
			float fT0 = hitNormal.Dot(vMerikomi);
			//�����߂��Ԃ��x�N�g�������߂�B
			//�����Ԃ��x�N�g���͕ǂ̖@���Ɏˉe���ꂽ�߂荞�݃x�N�g��+���a�B
			CVector3 vOffset;
			vOffset = hitNormal;
			vOffset *= -fT0 + m_radius;
			nextPosition += vOffset;
			CVector3 currentDir;
			currentDir = nextPosition - m_position;
			currentDir.Normalize();
			if (currentDir.Dot(originalDir) < 0.0f) {
				//�p�ɓ��������̃L�����N�^�̐U����h�~���邽�߂ɁA
				//�ړ��悪�t�����ɂȂ�����ړ����L�����Z������B
				nextPosition = m_position;
				break;
			}
		}
		else {
			//�ǂ��Ƃ�������Ȃ��̂ŏI���B
			break;
		}
		loopCount++;
		if (loopCount == 5) {
			break;
		}
	}

	//�ړ��m��B
	m_position = nextPosition;
	btRigidBody* btBody = m_rigidBody.GetBody();
	//���̂𓮂����B
	btBody->setActivationState(DISABLE_DEACTIVATION);
	btTransform& trans = btBody->getWorldTransform();
	//���̂̈ʒu���X�V�B
	trans.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));
	trans.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z));
	return m_position;
}

void HitObject::RemoveRigidBoby()
{
	g_physics.RemoveRigidBody(m_rigidBody);
}