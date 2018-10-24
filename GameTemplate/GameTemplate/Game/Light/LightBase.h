#pragma once
using namespace Light;

class LightBase
{
public:
	LightBase();
	~LightBase();
		
	
	void InitLight(void* anylight ,LightType lighttype,int sum);			//����1:���C�g�̍\����,����2:���C�g�̃^�C�v(enum)�B
	void InitPointLightSB(void* anylight);
	void InitSpotLightSB(void* anylight);
	void InitDirectionLightSB(void* anylight);
	void LightUpdateSubresource(const void* AnyLight);		//�X�V���ꂽ���C�g�̍\���́B
	void SendConstantBuffer();
	void SetlightParam(ligParam param)
	{
		ligP = param;
	}
	void setspecf(bool f)
	{
		specF = f;
	}

private:
	int lightsum = 0;
	/*struct nolig {
		int zero;
	};*/

	bool specF = false;
	ligParam ligP;
	
	ConstantBuffer m_cb;
	ConstantBuffer m_ligparamCB;


	StructuredBuffer pointlightSB;
	StructuredBuffer directionlightSB;
	StructuredBuffer spotlightSB;
	StructuredBuffer* thislightSB;


	SDirectionLight *SDir;
	SPointLight *SPoint;
	SSpotLight *SSpot;
	
	LightType Ligtype = no;
};


