#pragma once
#include "Physics/CapsuleCollider.h"
#include "Physics/RigidBody.h"
class CollisionDetection
{
	/// <summary>
	/// 内積の結果が1.0～-1.0の範囲を超えないようにする。
	/// </summary>
	/// <param name="dotresult">内積結果(float)</param>
	/// <returns>角度ラジアン(float)</returns>
	float Acos(float cosTheta)
	{
		float resulte = acosf(min(1.0f, max(-1.0f, cosTheta)));
		return resulte;
	}
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CollisionDetection();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~CollisionDetection();
	/// <summary>
	/// 当たった？
	/// </summary>
	/// <param name="oldbonepos">前フレームのボーンのポジション(CVector3)</param>
	/// <param name="nowbonepos">現在のボーンのポジション(CVector3)</param>
	/// <param name="radius">半径(float)</param>
	/// <returns>bool</returns>
	bool IsHIT(CVector3 oldbonepos, CVector3 nowbonepos, float radius);
	
};

