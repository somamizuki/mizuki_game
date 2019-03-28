#pragma once
#include "stdafx.h"
namespace Light {
	/// <summary>
	/// ディレクションライトの構造体
	/// </summary>
	struct SDirectionLight {
		CVector4 color;
		CVector4 Direction;
	};
	/// <summary>
	/// ポイントライトの構造体
	/// </summary>
	struct SPointLight {
		CVector4 color;
		CVector4 position;
		float range;
	};
	/// <summary>
	/// スポットライトの構造体
	/// </summary>
	struct SSpotLight {
		CVector4 color;
		CVector4 position;
		CVector4 Direction;
		float SpotAngle;				//ラジアンで入れる。
		float range;
	};
	/// <summary>
	/// ライトのパラメーター
	/// </summary>
	struct ligParam {
		CVector4 eyepos;
		float specPow;
	};
	/// <summary>
	/// ライトのタイプ
	/// </summary>
	enum LightType {
		nolig,
		Direction,
		Point,
		Spot,
	};
}