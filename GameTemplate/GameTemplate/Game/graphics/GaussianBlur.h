#pragma once
#include"Shader.h"
class GaussianBlur
{
public:
	GaussianBlur();
	~GaussianBlur();
	void Init(ID3D11ShaderResourceView* SRV);
	void Draw(sprite* postEffectSprite,ID3D11ShaderResourceView* srv);

	ID3D11ShaderResourceView* GetResultTextureSRV()
	{
		return m_downsampleRT[enRenderTarget_YBlur].GetRenderTargetSRV();
	}
private:
	void UpdateWeights();
	float m_blurIntensity = 50.0f;							//�u���[�̋����B�u���[�̃E�F�C�g�̌v�Z�Ŏg�p����܂��B
	enum EnRenderTarget {
		enRenderTarget_XBlur,		//X�u���[�̏������ݐ�ƂȂ郌���_�����O�^�[�Q�b�g�B
		enRenderTarget_YBlur,		//Y�u���[�̏������ݐ�ƂȂ郌���_�����O�^�[�Q�b�g�B
		enRenderTarget_Num,			//�����_�����O�^�[�Q�b�g�̖����B
	};
	static const int NUM_WEIGHTS = 8;	//�J�E�X�t�B���^�̏d�݂̐��B
	struct SBlurParam {
		float weights[NUM_WEIGHTS];
	};
	ID3D11ShaderResourceView* m_SRV;
	static const int NumDownSampling = 1;					//�_�E���T���v�����O��
	RenderTarget m_downsampleRT[enRenderTarget_Num];		//�_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g
	//D3D11_VIEWPORT m_downsampleVP[NumDownSampling];		//�_�E���T���v�����O�p�̃r���[�|�[�g
	float resoluteW;										//�𑜓xW
	float resoluteH;										//�𑜓xH
	Shader m_vsXBlur;						//X�u���[�p�̒��_�V�F�[�_�[�B
	Shader m_vsYBlur;						//Y�u���[�p�̒��_�V�F�[�_�[�B
	Shader m_psBlur;						//�u���[�p�̃s�N�Z���V�F�[�_�[�B
	SBlurParam m_blurParam;						//�u���[�p�̃p�����[�^�B
	ConstantBuffer m_blurCbGpu;				//�u���[�p�̒萔�o�b�t�@(GPU��)
};

