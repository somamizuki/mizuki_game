#pragma once
#include "level/Level.h"
#include "Player.h"
#include"m_camera.h"
#include"Enemy.h"
#include"Light/CDirectionLight.h"
#include"Light/CPointLight.h"
#include"graphics/sky.h"

class Class_of_NewGO:public GameObject
{
public:
	Class_of_NewGO(int No, const char* obj_name);
	~Class_of_NewGO();
	bool Start() { return true; }				//�X�^�[�g�֐�
	void Update();								//�A�b�v�f�[�g�֐�
	void Draw();								//�`��֐�
	std::vector<Enemy*>& GetEnemy()				//�G�l�~�[�̔z���n��
	{
		return m_enemy;
	}

private:
	
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
};

