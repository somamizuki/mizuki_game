#include "stdafx.h"
#include "sky.h"


sky::sky(int No, const char* obj_name) :GameObject(No, obj_name)
{
}


sky::~sky()
{
}
bool sky::Start()
{
	return true;
}

void sky::Init(const wchar_t* mapfilepath, const wchar_t* modelfilePath, CVector3 scale)
{
	m_scale = scale;
	m_skinmodel.Init(modelfilePath);
	m_skyCube.CreateFromDDSTextureFromFile(mapfilepath);
	m_skinmodel.FindMesh([&](auto& mat) 
	{
		ModelEffect* effect = reinterpret_cast<ModelEffect*>(mat->effect.get());
		effect->SetAlbedoTexture(m_skyCube.GetBody());
	});
	
}

void sky::Update()
{

	m_skinmodel.UpdateWorldMatrix(m_position, CQuaternion::Identity(), m_scale);
}

void sky::Draw()
{
	m_skinmodel.Draw(
		4,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}