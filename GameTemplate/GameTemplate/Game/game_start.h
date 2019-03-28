#pragma once
#include "level/Level.h"
#include"Light/CDirectionLight.h"
#include"Light/CPointLight.h"
#include"graphics/sky.h"
class game_start:public GameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="No"></param>
	/// <param name="obj_name"></param>
	game_start(int No, const char* obj_name);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~game_start();
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
	/// UI�`��֐�
	/// </summary>
	void UIDraw();
	/// <summary>
	/// Delete���ɌĂ΂��֐�
	/// </summary>
	void OnDestroy();
	/// <summary>
	/// �Q�[���X�^�[�g�t���O�̃Q�b�^�[
	/// </summary>
	/// <returns>bool</returns>
	bool GetGameStartflag()
	{
		return m_gamestart;
	}
private:
	CSoundSource	m_bgm;												//BGM
	CSoundSource	m_selectSE;											//�Z���N�gSE
	CSoundSource	m_decisionSE;										//����SE
	bool			m_startflag = false;								//�X�^�[�g�t���O
	enum MenuState {
		start,
		howtocontrol
	};
	MenuState		m_select = start;									//���j���[�X�e�[�g
	sky*			m_cubemap = nullptr;								//�L���[�u�}�b�v
	Level			m_level;											//���x���̃C���X�^���X
	CVector3		m_lightcameradir = CVector3::Zero();				//���C�g�J�����f�B���N�V����
	SPointLight		m_spointlight;										//�|�C���g���C�g�̍\����
	CPointLight		m_pointlig;											//�|�C���g���C�g
	SkinModel		m_sikinmodel;										//�X�L�����f��
	CVector3		m_position;											//�|�W�V����
	CQuaternion		m_rotation = CQuaternion::Identity();				//��]
	CVector3		m_cameraposition = CVector3::Zero();				//�J�����̃|�W�V����
	bool			m_gamestart = false;								//�Q�[���X�^�[�g�t���O
	Font			m_font;												//�t�H���g
	const CVector4	m_selectedstringcolor = {0.0f,1.0f,0.0f,1.0f};		//�I�����ꂽ�t�H���g�̃J���[
	const CVector4	m_noselectstringcolor = { 0.0f,1.0f,0.0f,0.2 };		//�I������Ă��Ȃ��t�H���g�̃J���[
};

