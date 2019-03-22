#include "stdafx.h"
#include "CollisionDetection.h"
#include "Physics/CollisionAttr.h"
#include <array> 
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

	//struct DebugDraw :public btIDebugDraw
	//{
	//	struct SConstantBuffer {
	//		CMatrix mView;
	//		CMatrix mProj;
	//	};
	//	int m_debugMode = btIDebugDraw::DBG_NoDebug;
	//	ID3D11DeviceContext* DeviceContext = nullptr;
	//	Primitive m_primitive;
	//	Shader m_vs;	//頂点シェーダー。
	//	Shader m_ps;	//ピクセルシェーダー。
	//	ConstantBuffer m_cb;
	//	static const int VERTEX_MAX = 1000000;
	//	std::array<CVector4, VERTEX_MAX> m_vertexBuffer;

	//	int m_numLine = 0;
	//	virtual void	drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
	//	{
	//		CVector3 i,j;
	//		i = from;
	//		j = to;
	//	}
	//	virtual void	drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

	//	virtual void	reportErrorWarning(const char* warningString);

	//	virtual void	draw3dText(const btVector3& location, const char* textString);

	//	virtual void	setDebugMode(int debugMode)override;

	//	virtual int		getDebugMode();
	//};
}

CollisionDetection::CollisionDetection()
{
}


CollisionDetection::~CollisionDetection()
{
}

bool CollisionDetection::IsHIT(CVector3 oldbonepos, CVector3 nowbonepos, float radius)
{
	CVector3 OldtoNowBone = nowbonepos - oldbonepos;
	CVector3 pos = nowbonepos - OldtoNowBone;
	CVector3 nextpos = nowbonepos;
	CapsuleCollider capsulecollider;
	if (OldtoNowBone.Length() <= 100.0f)
	{
		return false;
	}
	capsulecollider.Create(radius, OldtoNowBone.Length());
	OldtoNowBone.Normalize();
	RigidBody rigidbody;
	RigidBodyInfo rigidInfo;
	rigidInfo.collider = &capsulecollider;
	rigidInfo.mass = 0.0f;
	rigidInfo.rot = CQuaternion::Identity();
	rigidbody.Create(rigidInfo);
	rigidbody.GetBody()->setUserIndex(enCollisionAttr_BossEnemy);

	btTransform& trans = rigidbody.GetBody()->getWorldTransform();

	if (CVector3::AxisY().Dot(OldtoNowBone) <= 0.99999999999f)
	{
		float angle = Acos(CVector3::AxisY().Dot(OldtoNowBone));
		CVector3 axis = CVector3::Zero();
		axis.Cross(OldtoNowBone, CVector3::AxisY());
		CQuaternion rot = CQuaternion::Identity();
		rot.SetRotation(axis, -angle);


		trans.setRotation(btQuaternion(rot.x, rot.y, rot.z));

	}
	trans.setOrigin(btVector3(oldbonepos.x, oldbonepos.y, oldbonepos.z));

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

	/*btIDebugDraw debugdrawer;
	g_physics.GetDynamicWorld()->setDebugDrawer(&debugdrawer);
	g_physics.GetDynamicWorld()->debugDrawWorld();
	debugdrawer.draw();
	g_physics.GetDynamicWorld()->debugDrawObject(rigidbody.GetBody()->getWorldTransform(), rigidbody.GetBody()->getCollisionShape(),btVector3(0.0f, 1.0f, 0.0f));*/

	return callback.isHit;
}
