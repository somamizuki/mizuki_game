#pragma once
#include"SkinModelEffect.h"
#include "SkinModelDataManager.h"
class sky:public GameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="No"></param>
	/// <param name="obj_name"></param>
	sky(int No, const char* obj_name);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~sky();
	/// <summary>
	/// �������֐�
	/// </summary>
	/// <param name="mapfilepath">�e�N�X�`���[�t�@�C���p�X(L"filepath")</param>
	/// <param name="modelfilePath">���f���t�@�C���p�X(L"filepath")</param>
	/// <param name="scale">�X�P�[��(CVector3)</param>
	void Init(const wchar_t* mapfilepath, const wchar_t* modelfilePath, CVector3 scale);
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	/// <returns>bool</returns>
	bool Start();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	void Update();
	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw();
	/// <summary>
	/// �X�P�[�����Đݒ肷��֐�
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(CVector3 scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// �|�W�V�������Z�b�g����֐�
	/// </summary>
	/// <param name="pos">�|�W�V����(CVector3)</param>
	void SetPositon(CVector3& pos)
	{
		m_position = pos;
	}

private:
	SkinModel			m_skinmodel;					//�X�L�����f��
	ShaderResourceView	m_skycube;						//�L���[�u�}�b�v��SRV
	CVector3			m_scale;						//�X�P�[��
	CVector3			m_position = CVector3::Zero();	//�|�W�V����
};

