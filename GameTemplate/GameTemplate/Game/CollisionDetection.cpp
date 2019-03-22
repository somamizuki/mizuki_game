#include "stdafx.h"
#include "CollisionDetection.h"
#include "Physics/CollisionAttr.h"
namespace {
	struct SweepResult : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit = false;
		btCollisionObject* me = nullptr;		//自分自身。自分自身との衝突を除外するためのメンバ。
		virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			if (convexResult.m_hitCollisionObject != me && convexResult.m_hitCollisionObject->getUserIndex() == enCollisionAttr_Character)
			{
				isHit = true;
			}
			return 0.0f;
		}
	};
}

CollisionDetection::CollisionDetection()
{
}


CollisionDetection::~CollisionDetection()
{
}

bool CollisionDetection::CleateCollider(CVector3 oldbonepos, CVector3 nowbonepos, float radius)
{
	CVector3 OldtoNowBone = nowbonepos - oldbonepos;
	CVector3 pos = nowbonepos - OldtoNowBone;
	CVector3 nextpos = nowbonepos;
	CapsuleCollider capsulecollider;

	capsulecollider.Create(OldtoNowBone.Length(), radius);
	OldtoNowBone.Normalize();
	RigidBody rigidbody;
	RigidBodyInfo rigidInfo;
	rigidInfo.collider = &capsulecollider;
	rigidInfo.mass = 0.0f;
	rigidInfo.rot = CQuaternion::Identity();
	rigidbody.Create(rigidInfo);
	rigidbody.GetBody()->setUserIndex(enCollisionAttr_BossEnemy);

	//CVector3 nextpos=

	btTransform& trans = rigidbody.GetBody()->getWorldTransform();

	if (CVector3::AxisY().Dot(OldtoNowBone) <= 0.999999999999f)
	{
		float angle = Acos(CVector3::AxisY().Dot(OldtoNowBone));
		CVector3 axis = CVector3::Zero();
		axis.Cross(OldtoNowBone, CVector3::AxisY());
		CQuaternion rot = CQuaternion::Identity();
		rot.SetRotation(axis, -angle);


		trans.setRotation(btQuaternion(rot.x, rot.y, rot.z));

	}
	trans.setOrigin(btVector3(oldbonepos.x, oldbonepos.y, oldbonepos.z));

	g_physics.AddRigidBody(rigidbody);
	SweepResult callback;
	callback.me = rigidbody.GetBody();

	btTransform fromWorld;
	fromWorld.setIdentity();
	CVector3 fromworld = oldbonepos;
	fromWorld.setOrigin(btVector3(fromworld.x, fromworld.y, fromworld.z));
	btTransform toWorld;
	toWorld.setIdentity();
	CVector3 toworld = nowbonepos;
	toWorld.setOrigin(btVector3(toworld.x, toworld.y, toworld.z));
	g_physics.ConvexSweepTest((const btConvexShape*)capsulecollider.GetBody(), fromWorld, toWorld, callback);

	return callback.isHit;
}
