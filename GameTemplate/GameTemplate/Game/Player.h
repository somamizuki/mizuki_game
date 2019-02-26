#pragma once
#include "ObjectInfo.h"
#include"character/HitObject.h"
#include"Enemy.h"
#include"SpriteEffect.h"
#include"level/Level.h"
#include "missileRechargeHUD.h"
#include"HPGaugeHUD.h"

class m_camera;
class bullet;
class Class_of_NewGO;
using namespace PlayerInfo;
class Player:public GameObject
{
public:
	Player(int No, const char* obj_name);
	~Player();
	bool Start();								//�X�^�[�g�֐�
	void Update();								//�A�b�v�f�[�g�֐�
	void Draw();								//�`��֐�
	void EffectDraw();
	void PostDraw();							//��O�ɕ`�悵�������̂̕`��
	void UIDraw();
	void OnDestroy();
	void setposition(CVector3 pos)				//�|�W�V�����̃Z�b�^�[
	{
		m_position = pos;
	}
	void setrot(CQuaternion rot)				//��]�̃Z�b�^�[
	{
		m_rotation = rot;
	}
	const CVector3& Getpos() const				//�|�W�V�����̃Q�b�^�[
	{
		return m_position;
	}

	const CVector3& Getforward() const			//�O�����̃Q�b�^�[
	{
		return m_forward;
	}

	const CVector3& Getrite() const				//�E�����̃Q�b�^�[
	{
		return m_rite;
	}

	const CVector3& Getup() const				//������̃Q�b�^�[
	{
		return m_up;
	}

	const CVector3& Get_PlayerMove() const		//�v���C���[�̈ړ����x�̃Q�b�^�[
	{
		return movespeed;
	}


	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}

	void SetHP(int damage)
	{
		m_playerParam.HP -= damage;
	}
	
private:
	//�v���C���[�̃p�����[�^�[
	struct playerParam
	{
		int HP = 50;
	};


	playerParam m_playerParam;
	const float HPMAX = m_playerParam.HP;

	SkinModel m_model;									//�X�L�����f���B
	CVector3 m_position = CVector3::Zero();				//�v���C���[�̃|�W�V����
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 movespeed = CVector3::Zero();				//movespeed
	CMatrix rot_M;
	CVector3 m_forward;
	CVector3 m_rite;
	CVector3 m_up;
	ShaderResourceView aimSRV;
	sprite aimsprite;
	ShaderResourceView LockOnSRV;
	sprite LockOnSprite;
	CVector3 LockOnEnemyPos = { 0.0f,0.0f,0.0f };


	float pad_X;									//�p�b�hX�̓��͗�
	float pad_Y;									//�p�b�hY�̓��͗�
	const float DefaultSpeed = 2000.0f;					//�f�t�H���g�̑��x
	const float BoostSpeed = 4000.0f;					//�u�[�X�g���̑��x
	const float RotSpeed_X = 3.0f;						//Z������̉�]�X�s�[�h
	const float RotSpeed_Y = 2.0f;						//X������̉�]�X�s�[�h
	const float RotSpeed_Tw = 0.3f;						//�G�C�������������ϐ�

	
	const float bulletspan = 3.0f;
	float ritebulletTime = 0.0f;
	float leftbulletTime = 0.0f;
	float leftmissileGaugelevel = 1.0f;
	float ritemissileGaugelevel = 1.0f;

	bool LockOnflag = false;

	float Speed = 0.0f;

	void playermove();								//�v���C���[�̈ړ��֐�
	void playerreturn();							//�~�b�V�����G���A�O�ɏo�Ȃ��悤�ɂ���
	void vector();									//�v���C���[�̑O�E��̃x�N�g�����v�Z����֐�
	void bulletManager();
	Enemy* LockOnManager();
	Enemy* prevLockOnEnemy = nullptr;
	void spritemanager();
	float Acos(float dotresult)				//���ς̌��ʂ�1.0�`-1.0�͈̔͂𒴂��Ȃ��悤�ɂ���B
	{
		float resulte = acosf(min(1.0f, max(-1.0f, dotresult)));
		return resulte;
	}

	m_camera* camera = nullptr;						//�J�����̃|�C���^�[
	Class_of_NewGO* CofNG = nullptr;
	bullet* RiteBullet = nullptr;
	bullet* LeftBullet = nullptr;
	std::vector<Enemy*> Enemys;
	enum PlayerState								//�v���C���[�̃X�e�[�g
	{
		Nomal,		//�ʏ�
		Return		//���_�ɖ߂�(�~�b�V�����͈͂𒴂�����)
	};
	PlayerState pState = Nomal;
	HitObject m_characon;
	//ID3D11ShaderResourceView* g_nomalMapSRV = nullptr;


	struct Engin
	{
		SpriteEffect spriteeffect;
		CVector3 toEngin;
	};
	std::vector<Engin*> spriteeffect;
	ShaderResourceView m_srv;

	Level playerenginlevel;		//�G���W���̃|�W�V���������������x��

	missileRechargeHUD m_leftRechargeHUD;
	missileRechargeHUD m_riteRechargeHUD;
	HPGaugeHUD m_hpHUD;

};

