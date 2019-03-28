#pragma once
#include "level/Level.h"
#include "Player.h"
#include"GameCamera.h"
#include"Enemy.h"
#include"Light/CDirectionLight.h"
#include"Light/CPointLight.h"
#include"graphics/sky.h"
#include "Timer.h"
#include "Result.h"
#include "Game.h"
#include "Effect.h"
#include "BossEnemy.h"

class Class_of_NewGO :public GameObject
{
public:
	/// <summary>
	/// �N���X�I�u�j���[�S�[�̃R���X�g���N�^
	/// </summary>
	/// <param name="No">�D��x</param>
	/// <param name="obj_name">���O</param>
	Class_of_NewGO(int No, const char* obj_name);
	/// <summary>
	/// �N���X�I�u�j���[�S�[�̃R���X�g���N�^
	/// </summary>
	~Class_of_NewGO();
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
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
	/// �G�t�F�N�g�`��֐�
	/// </summary>
	void EffectDraw();
	/// <summary>
	/// UI�`��֐�
	/// </summary>
	void UIDraw();
	/// <summary>
	/// Delete���ɌĂ΂��֐�
	/// </summary>
	void OnDestroy();
	/// <summary>
	/// �G�l�~�[�̔z��̃Q�b�^�[
	/// </summary>
	/// <returns>�G�l�~�[�̔z��</returns>
	std::vector<Enemy*>& GetEnemy()				//�G�l�~�[�̔z���n��
	{
		return *&m_enemy;
	}
	/// <summary>
	/// HitSE�̃Q�b�^�[
	/// </summary>
	/// <returns>CSoundSource</returns>
	CSoundSource* GetHitSE()
	{
		return &m_hitSE;
	}

	/// <summary>
	/// lockonSE�̃Q�b�^�[
	/// </summary>
	/// <returns>CSoundSource</returns>
	CSoundSource* GetLockOnSE()
	{
		return &m_lockonSE;
	}
	/// <summary>
	/// fireSE�̃Q�b�^�[
	/// </summary>
	/// <returns>CSoundSource</returns>
	CSoundSource* GetFireSE()
	{
		return &m_fireSE;
	}
	/// <summary>
	/// �Q�[���N���A�t���O�̃Q�b�^�[
	/// </summary>
	/// <returns>bool</returns>
	bool GameClear()
	{
		return m_gameclearflag;
	}
	/// <summary>
	/// �g�p���Ă��Ȃ�
	/// </summary>
	/// <param name="game"></param>
	void SetGameMain(Game* game)
	{
		m_game = game;
	}
	/// <summary>
	/// Result�̃Q�b�^�[
	/// </summary>
	/// <returns>Result*</returns>
	Result* GetResult()
	{
		return &m_result;
	}
	/// <summary>
	/// Effect�̃Q�b�^�[
	/// </summary>
	/// <returns>Effect*</returns>
	Effect* GetEffect()
	{
		return &m_effect;
	}
	/// <summary>
	/// �{�X�̃Q�b�^�[
	/// </summary>
	/// <returns>BossEnemy*</returns>
	BossEnemy* GetBossEnemy()
	{
		return m_bossenemy;
	}
	/// <summary>
	/// WaveCounter�̃Q�b�^�[
	/// </summary>
	/// <returns>int</returns>
	int GetWaveCounter()
	{
		return m_wavecounter;
	}
private:

	CSoundSource			m_bgm;									//BGM
	CSoundSource			m_bgmendwave;							//�ŏIWave�p��BGM
	CSoundSource			m_hitSE;								//�~�T�C����������������SE
	CSoundSource			m_lockonSE;								//���b�N�I������SE
	CSoundSource			m_fireSE;								//�~�T�C�����ˎ���SE


	Player*					m_player = nullptr;						//�v���C���[�̃|�C���^�[
	std::vector<Enemy*>		m_enemy;								//�G�l�~�[�̔z��
	Level					m_level;								//���x���̃C���X�^���X
	CDirectionLight			m_dirlig;								//�f�B���N�V�������C�g�̃C���X�^���X
	CPointLight				m_pointlig;								//�|�C���g���C�g
	GameCamera*				m_camera = nullptr;						//�J�����̃|�C���^�[
	sky*					m_cubemap = nullptr;					//�L���[�u�}�b�v�N���X�̃|�C���^�[
	SkinModel				m_sun;									//�P���̃X�L�����f��
	CVector3				m_lightcameradir = CVector3::Zero();	//�V���h�E�}�b�v�p�J�����̃f�B���N�V����
	SPointLight				m_spointlight;							//�|�C���g���C�g�̍\����
	Game*					m_game = nullptr;						//Game�N���X�̃|�C���^�[
	Timer					m_timer;								//Timer�N���X�̃|�C���^�[
	bool					m_gameclearflag = false;				//�N���A�������ǂ����̃t���O
	int						m_wavecounter = 1;
	Result					m_result;								//Result�N���X�̃C���X�^���X
	bool					m_resultdrawflag = false;				//���U���g��`�悷��t���O
	CVector3				m_playerposition;						//�v���C���[�̃|�W�V����
	Effect					m_effect;								//�G�t�F�N�g�̃C���X�^���X
	BossEnemy*				m_bossenemy = nullptr;					//�{�X�̃|�C���^�[
};

