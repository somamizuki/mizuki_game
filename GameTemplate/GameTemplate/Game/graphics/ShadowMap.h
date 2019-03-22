#pragma once
#include "RenderTarget.h"
class SkinModel;
class ShadowMap
{
public:
	ShadowMap();
	~ShadowMap();
	CMatrix GetLighViewMatrix() const
	{
		return m_lightViewMatrix;
	}

	CMatrix GetLightProjMatrix() const
	{
		return m_lightProjMatrix;
	}

	void UpdateFromLightTarget(CVector3 lightCameraPos, CVector3 lightCameraTarget);

	void UpdateFromLightDirection(CVector3 lightCameraPos, CVector3 lightDir);

	void RenderToShadowMap();

	void RegistShadowCaster(SkinModel* shadowCaster)
	{
		m_shadowCasters.push_back(shadowCaster);
	}

	void ShadowMapDraw();

	ID3D11ShaderResourceView* GetShadowMapSRV()
	{
		return m_shadowMapRT.GetRenderTargetSRV();
	}
private:
	CVector3 m_lightCameraPosition = CVector3::Zero();	//���C�g�J�����̎��_�B
	CVector3 m_lightCameraTarget = CVector3::Zero();	//���C�g�J�����̒����_�B
	CMatrix m_lightViewMatrix = CMatrix::Identity();	//���C�g�r���[�s��B
	CMatrix m_lightProjMatrix = CMatrix::Identity();	//���C�g�v���W�F�N�V�����s��B
	RenderTarget m_shadowMapRT;						//�V���h�E�}�b�v��`�悷�郌���_�����O�^�[�Q�b�g�B
	std::vector< SkinModel*> m_shadowCasters;	//�V���h�E�L���X�^�[�̔z��B
};

