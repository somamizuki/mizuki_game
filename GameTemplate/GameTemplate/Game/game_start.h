#pragma once
#include "level/Level.h"
#include"Light/CDirectionLight.h"
#include"Light/CPointLight.h"
#include"graphics/sky.h"
class game_start:public GameObject
{
public:
	game_start(int No, const char* obj_name);
	~game_start();

	bool Start();
	void Update();
	void Draw();
	void UIDraw();
	bool GetGameStartflag()
	{
		return gamestart;
	}

private:
	CSoundEngine m_soundEngine;				//�T�E���h�G���W���B
	CSoundSource m_bgm;						//BGM
	CSoundSource m_selectSE;				//�Z���N�gSE
	CSoundSource m_decisionSE;				//����SE
	float waitTimer = 0.0f;
	bool startTimer = false;
	enum MenuState {
		start,
		howtocontrol
	};
	MenuState Select = start;
	sky* map = nullptr;
	Level level;								//���x���̃C���X�^���X
	CVector3 SCamDir = CVector3::Zero();
	SPointLight spoint;			//�|�C���g���C�g�̍\����
	CPointLight m_pointlig;						//�|�C���g���C�g
	SkinModel m_sikinmodel;
	CVector3 m_position;
	CQuaternion m_rotation = CQuaternion::Identity();
	CVector3 camerapos = CVector3::Zero();
	bool gamestart = false;
	Font m_font;
	CVector4 SelectedStringColor = CVector4::White();
	CVector4 noSelectStringColor = {1.0f,1.0f,1.0f,0.3f};

};

