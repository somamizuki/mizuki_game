#pragma once
#include "game_start.h"
class Class_of_NewGO;
class Game:public GameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="No"></param>
	/// <param name="obj_name"></param>
	Game(int No, char* obj_name);
	~Game();
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
private:
	/*�Q�[���̃X�e�[�g*/
	enum gamestate {
		title,
		start,
		stop,
		end
	};
	gamestate state = end;					//�Q�[���X�e�[�g
	CSoundEngine m_soundEngine;				//�T�E���h�G���W���B
	Class_of_NewGO *newObject = nullptr;	//Class_of_NewGO�̃|�C���^�[
	game_start* gamestart = nullptr;		//game_start�̃|�C���^�[
	ShadowMap shadowMap;					//ShadowMap�̃C���X�^���X
	bool stopflag = false;					//��~�t���O
};

