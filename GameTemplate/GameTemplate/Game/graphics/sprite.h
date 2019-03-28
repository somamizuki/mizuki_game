#pragma once
#include"ShaderResourceView.h"
#include"UnorderedAccessView.h"
#include"Primitive.h"
#include"ConstantBuffer.h"
#include"StructuredBuffer.h"

class sprite:Noncopyable
{
public:
	static const CVector2 DEFAULT_PIVOT;	//�f�t�H���g�s�|�b�g
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	sprite();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~sprite();
	/// <summary>
	/// �������֐�
	/// </summary>
	/// <param name="tex">ID3D11ShaderResourceView*</param>
	/// <param name="w">��</param>
	/// <param name="h">����</param>
	void Init(ID3D11ShaderResourceView* tex, float w, float h);
	/// <summary>
	/// �t���X�N���[���`��p�̏������֐�
	/// </summary>
	void FullScreenInit();
	/// <summary>
	/// �����[�X�֐�
	/// </summary>
	void Release();
	/// <summary>
	/// �V�F�[�_�[�̃Z�b�^�[
	/// </summary>
	/// <param name="filepathVS">VS�V�F�[�_�[(L"filepath")</param>
	/// <param name="filepathPS">PS�V�F�[�_�[(L"filepath")</param>
	void SetShader(const char* filepathVS, const char* filepathPS)
	{
		m_ps.Load(filepathPS, "PSMain", Shader::EnType::PS);
		m_vs.Load(filepathVS, "VSMain", Shader::EnType::VS);
	}
	/// <summary>
	///	�V�F�[�_�[�̃Z�b�^�[
	/// </summary>
	/// <param name="VS">Shader* VS</param>
	/// <param name="PS">Shader* PS</param>
	void SetShader(Shader* VS, Shader* PS)
	{
		m_ps = *PS;
		m_vs = *VS;
	}
	/// <summary>
	/// �e�N�X�`���[�̃Z�b�^�[
	/// </summary>
	/// <param name="tex">ID3D11ShaderResourceView* tex</param>
	void SetTexture(ID3D11ShaderResourceView* tex)
	{
		m_textureSRV = tex;
	}
	/// <summary>
	/// �r���[�s��ƃv���W�F�N�V�����s��̃Z�b�^�[
	/// </summary>
	/// <param name="viewM">�r���[�s��(CMatrix)</param>
	/// <param name="projM">�v���W�F�N�V�����s��(CMatrix)</param>
	void SetViewProj(CMatrix& viewM,CMatrix& projM)
	{
		m_view = viewM;
		m_proj = projM;
	}
	/// <summary>
	/// �v���W�F�N�V�����s��̃Z�b�^�[
	/// </summary>
	/// <param name="projM">�v���W�F�N�V�����s��(CMatrix)</param>
	void SetProj(CMatrix& projM)
	{
		m_proj = projM;
	}
	/// <summary>
	/// �J���[�̃Z�b�^�[(���l�̒����Ȃ�)
	/// </summary>
	/// <param name="mulColor">const CVector4& mulColor</param>
	void SetMulColor(const CVector4& mulColor)
	{
		m_mulColor = mulColor;
	}
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	/// <param name="trans">���s�ړ�(CVector3)</param>
	/// <param name="rot">��](CQuaternion)</param>
	/// <param name="scale">�X�P�[��(CVector3)</param>
	/// <param name="pivot">�s�|�b�g(CVector2)</param>
	void Update(const CVector3& trans, const CQuaternion& rot, const CVector3& scale, const CVector2& pivot = DEFAULT_PIVOT);
	/// <summary>
	/// �`��֐�
	/// </summary>
	/// <param name="renderContext">ID3D11DeviceContext</param>
	void Draw(ID3D11DeviceContext& renderContext);
	/// <summary>
	/// �|�X�g�G�t�F�N�g�̕`��֐�
	/// </summary>
	/// <param name="renderContext">ID3D11DeviceContext</param>
	void PostEffectDraw(ID3D11DeviceContext& renderContext);
private:
	/// <summary>
	/// �X�v���C�g�̍\����
	/// </summary>
	struct SSpriteCB {
		CMatrix WVP;
		CVector4 mulColor;
	};
	CVector3					m_position = CVector3::Zero();			//�|�W�V����
	CQuaternion					m_rotation = CQuaternion::Identity();	//��]
	CVector3					m_scale = CVector3::One();				//�X�P�[��
	CMatrix						m_world = CMatrix::Identity();			//���[���h�s��
	Shader						m_ps;									//�s�N�Z���V�F�[�_�[
	Shader						m_vs;									//���_�V�F�[�_�[
	CVector4					m_mulColor = CVector4::White();			//�J���[
	Primitive					m_primitive;							//�v���~�e�B�u
	ID3D11ShaderResourceView*	m_textureSRV = nullptr;					//�e�N�X�`���[��SRV
	ConstantBuffer				m_cb;									//�萔�o�b�t�@�[
	ID3D11SamplerState*			m_samplerState = nullptr;				//�T���v���[�X�e�[�g
	CVector2					m_size = CVector2::Zero();				//�T�C�Y
	CMatrix						m_view;									//�r���[�s��
	CMatrix						m_proj;									//�v���W�F�N�V�����s��
	bool						f_update = false;						//�A�b�v�f�[�g�֐����Ă΂ꂽ�t���O
};

