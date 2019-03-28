#pragma once
#include"GaussianBlur.h"
#include"Shader.h"
class Bloom
{
public:
	Bloom();
	~Bloom();
	void Init();
	void Update();


private:
	ID3D11SamplerState* m_samplerState = nullptr;			//�T���v���X�e�[�g�B
	ID3D11BlendState*	m_disableBlendState = nullptr;		//�A���t�@�u�����f�B���O�𖳌��ɂ���u�����f�B���O�X�e�[�g�B
	ID3D11BlendState*	m_finalBlendState = nullptr;		//�ŏI�����p�̃u�����f�B���O�X�e�[�g�B
	static const int	NumDownSampling = 4;				//�_�E���T���v�����O��
	GaussianBlur		m_gaussianblur[NumDownSampling];
	RenderTarget		m_luminanceRT;						//�P�x���o�p�����_�[�^�[�Q�b�g
	RenderTarget		m_blurCombineRT;
	float				resoluteW;							//�𑜓xW
	float				resoluteH;							//�𑜓xH
	Shader				m_vs;								//�������Ȃ����_�V�F�[�_�[�B
	Shader				m_psLuminance;						//�P�x���o�p�̃s�N�Z���V�F�[�_�[�B
	Shader				m_psCombine;						//�ڂ����摜�����p�̃s�N�Z���V�F�[�_�[�B
	Shader				m_psFinal;							//�ŏI�����p�̃s�N�Z���V�F�[�_�[�B
	sprite				m_sprite;							//�X�v���C�g
	bool				createF = false;					//RT������ꂽ�t���O
};