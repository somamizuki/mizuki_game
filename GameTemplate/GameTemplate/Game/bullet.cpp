#include "stdafx.h"
#include "bullet.h"



bullet::bullet(int No, const char* obj_name) : GameObject(No, obj_name)
{
}


bullet::~bullet()
{

}

bool bullet::Start()
{
	
	m_tama.Init(L"Assets/modelData/kyutai.cmo");					//�ʂ̃��f���C�j�b�g
	m_player = game_obj->FindGO<Player>("player");					//�v���C���[�̌���
	CoN = game_obj->FindGO<Class_of_NewGO>("newObject");			//�����ȃN���X��new����N���X������
	tamadir = m_player->Getforward();								//�ʂ̃f�B���N�V�����Ƀv���C���[�̃t�H���[�h����
	speed = m_player->Get_PlayerMove().Length()+bulletspeed;		//�ʂ̍ŏI�X�s�[�h
	bulletpos = m_player->Getpos() + tamadir *500.0f;				//�o���b�g�̃|�W�V�������v���C���[�̑O��500�̈ʒu�ɃZ�b�g
	return true;
}

void bullet::Update()
{
	bulletpos += tamadir * (speed*(1.0f / 60.0f));					//�o���b�g��i�߂Ă���
	CVector3 e_to_b = CVector3::Zero();								//�G�l�~�[����o���b�g�ւ̃x�N�g��
	if (!this->GetDeath_f())										//�����̎��S�t���O�������Ă��Ȃ����
	{
		if (!CoN->GetDeath_f())										//�����ȃN���X��new����N���X�̎��S�t���O�������Ă��Ȃ����
		{
			for (auto& enemy : CoN->GetEnemy())
			{
				e_to_b = bulletpos - enemy->Getpos();				//�G�l�~�[����o���b�g�ւ̃x�N�g�������߂�
				if (e_to_b.Length() < 300.0f)						//e_to_b�̒�����300.0f�����Ȃ�
				{
					game_obj->DeleteGO(enemy);						//�����ɍ������G�l�~�[�̎��S�t���O�����Ă�
					CoN->GetEnemy().erase(std::remove(				//CoN�̃G�l�~�[���X�g�̗v�f������(�C���[�X�����[�u�C�f�I��)
						CoN->GetEnemy().begin(),					//���������ŏ����Ƃ����䏈��
						CoN->GetEnemy().end(), enemy),
						CoN->GetEnemy().end());
					game_obj->DeleteGO(this);						//�G�l�~�[�Ɠ��������̂Ŏ���������
				}
			}
		}
		
	}
	
	m_tama.UpdateWorldMatrix(bulletpos, CQuaternion::Identity(), { 0.05f,0.05f,0.05f });		//���[���h�}�g���N�X�̍X�V
}

void bullet::Draw()
{
	m_tama.Draw(																				//�ʂ̕`��
		1,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}