#pragma once
#include"SkinModelEffect.h"
#include "SkinModelDataManager.h"
class sky:public GameObject
{
public:
	sky(int No, const char* obj_name);
	~sky();
	void Init(const wchar_t* mapfilepath, const wchar_t* modelfilePath, CVector3 scale);
	bool Start();
	void Update();
	void Draw();
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}
	void SetPositon(CVector3& pos)
	{
		m_position = pos;
	}

private:
	SkinModel m_skinmodel;
	ShaderResourceView m_skyCube;
	Shader m_psSkyShader;
	CVector3 m_scale;
	CVector3 m_position = CVector3::Zero();
};

