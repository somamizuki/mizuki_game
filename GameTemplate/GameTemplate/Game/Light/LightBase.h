#pragma once

namespace Light {
	class LightBase
	{
	public:
		LightBase();
		~LightBase();
		struct SDirectionLight {
			CVector4 color;
			CVector4 Direction;
		};

		struct SPointLight {
			CVector4 color;
			CVector4 position;
		};

		struct SSpotLight {
			CVector4 color;
			CVector4 position;
			CVector4 Direction;
			float SpotAngle;				//ÉâÉWÉAÉìÇ≈ì¸ÇÍÇÈÅB
		};

		void InitLight(SDirectionLight* dirLight );
		void InitLight(SPointLight* pointLight);
		void InitLight(SSpotLight* spotLight);
		void LightUpdateSubresource();
	private:
		ConstantBuffer m_cb;
		SDirectionLight *SDir;
		SPointLight *SPoint;
		SSpotLight *SSpot;
		enum LightType {
			Direction,
			Point,
			Spot,
			no
		};
		LightType Ligtype = no;
	};
}


