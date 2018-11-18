#pragma once
#include "stdafx.h"
namespace Light {
	struct SDirectionLight {
		CVector4 color;
		CVector4 Direction;
	};

	struct SPointLight {
		CVector4 color;
		CVector4 position;
		float range;
	};

	struct SSpotLight {
		CVector4 color;
		CVector4 position;
		CVector4 Direction;
		float SpotAngle;				//ÉâÉWÉAÉìÇ≈ì¸ÇÍÇÈÅB
		float range;
	};

	struct ligParam {
		CVector4 eyepos;
		float specPow;
	};

	enum LightType {
		nolig,
		Direction,
		Point,
		Spot,
	};
}