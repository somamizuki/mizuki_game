#pragma once
#include "RenderTarget.h"
class SkinModel;
class ShadowMap
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ShadowMap();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ShadowMap();
	/// <summary>
	/// ���C�g�̃r���[�}�g���N�X
	/// </summary>
	/// <returns>CMatrix</returns>
	CMatrix GetLighViewMatrix() const
	{
		return m_lightViewMatrix;
	}
	/// <summary>
	/// ���C�g�̃r���[�}�g���N�X
	/// </summary>
	/// <returns>CMatrix</returns>
	CMatrix GetLightProjMatrix() const
	{
		return m_lightProjMatrix;
	}
	/// <summary>
	/// ���C�g�J�����̕������v�Z����֐�
	/// </summary>
	/// <param name="lightCameraPos">���C�g�J�����̃|�W�V����(CVector3)</param>
	/// <param name="lightCameraTarget">���C�g�J�����̃^�[�Q�b�g(CVector3)</param>
	void UpdateFromLightTarget(CVector3 lightCameraPos, CVector3 lightCameraTarget);
	/// <summary>
	/// ���C�g�J�����̕�������r���[�s��ƃv���W�F�N�V�����s����X�V����֐�
	/// </summary>
	/// <param name="lightCameraPos">���C�g�J�����̃|�W�V����(CVector3)</param>
	/// <param name="lightDir">���C�g�J�����̕���(CVector3)</param>
	void UpdateFromLightDirection(CVector3 lightCameraPos, CVector3 lightDir);
	/// <summary>
	/// �V���h�E�L���X�^�[�ɓo�^���ꂽ���f�����V���h�E�}�b�v�p�̃����_�����O�^�[�Q�b�g�ɕ`�悷��֐�
	/// </summary>
	void RenderToShadowMap();
	/// <summary>
	/// �V���h�E�L���X�^�[��o�^����֐�
	/// </summary>
	/// <param name="shadowCaster"></param>
	void RegistShadowCaster(SkinModel* shadowCaster)
	{
		m_shadowCasters.push_back(shadowCaster);
	}
	/// <summary>
	/// �V���h�E�}�b�v�̕`��֐�
	/// </summary>
	void ShadowMapDraw();
	/// <summary>
	/// �V���h�E�}�b�vSRV�̃Q�b�^�[
	/// </summary>
	/// <returns>ID3D11ShaderResourceView*</returns>
	ID3D11ShaderResourceView* GetShadowMapSRV()
	{
		return m_shadowMapRT.GetRenderTargetSRV();
	}
private:
	CVector3					m_lightCameraPosition = CVector3::Zero();	//���C�g�J�����̎��_�B
	CVector3					m_lightCameraTarget = CVector3::Zero();		//���C�g�J�����̒����_�B
	CMatrix						m_lightViewMatrix = CMatrix::Identity();	//���C�g�r���[�s��B
	CMatrix						m_lightProjMatrix = CMatrix::Identity();	//���C�g�v���W�F�N�V�����s��B
	RenderTarget				m_shadowMapRT;								//�V���h�E�}�b�v��`�悷�郌���_�����O�^�[�Q�b�g�B
	std::vector< SkinModel*>	m_shadowCasters;							//�V���h�E�L���X�^�[�̔z��B
};

