#pragma once
#include"Player.h"
#include"Class_of_NewGO.h"
#include"bulletinfo.h"

using namespace BulletInfo;
class bullet:public GameObject
{
public:
	bullet(int No, const char* obj_name);
	~bullet();

	bool Start();									//�X�^�[�g�֐�(�������Ƃ�)
	void Update();									//�X�V����
	void Draw();									//�`��

	const CVector3 Getpos() const					//�|�W�V������������֐�
	{
		return bulletpos;
	}

private:
	//����
	SkinModel m_tama;								//�ʂ̃��f��
	CVector3 tamadir = CVector3::Zero();			//�ʂ̃f�B���N�V����
	CVector3 bulletpos = CVector3::Zero();			//�ʂ̃|�W�V����
	float speed = 0.0f;								//�ʂ̍ŏI���x
	Player* m_player = nullptr;						//�v���C���[�̃|�C���^�[
	Class_of_NewGO* CoN = nullptr;					//�����ȃN���X��new����N���X�̃|�C���^�[
};

