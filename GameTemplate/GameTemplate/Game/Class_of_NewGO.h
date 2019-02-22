#pragma once
#include "level/Level.h"
#include "Player.h"
#include"m_camera.h"
#include"Enemy.h"
#include"Light/CDirectionLight.h"
#include"Light/CPointLight.h"
#include"graphics/sky.h"
#include "Game.h"
class Class_of_NewGO:public GameObject
{
public:
	Class_of_NewGO(int No, const char* obj_name);
	~Class_of_NewGO();
	bool Start();				//�X�^�[�g�֐�
	void Update();								//�A�b�v�f�[�g�֐�
	void Draw();								//�`��֐�
	void OnDestroy();
	std::vector<Enemy*>& GetEnemy()				//�G�l�~�[�̔z���n��
	{
		return *&m_enemy;
	}

	CSoundSource* GetHitSE()
	{
		return &m_HitSE;
	}
	CSoundEngine* GetSoundEngine()
	{
		return &m_soundEngine;
	}

	CSoundSource* GetlockonSE()
	{
		return &m_lockonSE;
	}

	CSoundSource* GetfireSE()
	{
		return &m_fireSE;
	}

	bool GameClear()
	{
		return gameClear;
	}

	void SetGameMain(Game* game)
	{
		m_game = game;
	}


private:
	CSoundEngine m_soundEngine;				//�T�E���h�G���W���B
	CSoundSource m_bgm;						//BGM
	CSoundSource m_HitSE;						//BGM
	CSoundSource m_lockonSE;
	CSoundSource m_fireSE;


	Player* player = nullptr;					//�v���C���[�̃|�C���^�[
	std::vector<Enemy*> m_enemy;				//�G�l�~�[�̔z��
	Level level;								//���x���̃C���X�^���X
	CDirectionLight m_dirlig;					//�f�B���N�V�������C�g�̃C���X�^���X
	CPointLight m_pointlig;						//�|�C���g���C�g
	m_camera* camera = nullptr;					//�J�����̃|�C���^�[
	sky* map = nullptr;
	SkinModel Sun;
	CVector3 SCamDir = CVector3::Zero();
	SPointLight spoint;			//�|�C���g���C�g�̍\����
	Game* m_game = nullptr;

	bool gameClear = false;		//�N���A�������ǂ����̃t���O

	CVector3 pos;
};

