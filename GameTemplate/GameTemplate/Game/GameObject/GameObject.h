#pragma once
//#include "GameObjectManajer.h"
class GameObject:Noncopyable
{
public:
	//�D��x,�I�u�W�F�N�g�̖��O
	GameObject(int No, const char* obj_name);
	//{
	//	game_obj.Set_push_list(this, No);
	//	this_name = obj_name;
	//}
	virtual ~GameObject()
	{

	}
	virtual bool Start() { return true; }//�X�^�[�g�֐�(�������Ƃ�)
	virtual void Update(){}				 //�X�V����
	virtual void Draw(){}				 //�`��
	virtual void EffectDraw(){}			 //�G�t�F�N�g�̕`��
	virtual void PostDraw(){}			 //��O�ɕ`�悵�������̂̕`��
	virtual void UIDraw() {}			 //UI�Ƃ��̕`��
	const char* GetName()				 //�N���X���̃Q�b�^�[
	{
		return this_name;
	}
	bool Get_isStart()					 //�X�^�[�g�t���O���Q�b�g����֐�
	{
		return m_start;
	}
	void Set_isStart(bool start_f)		 //�X�^�[�g�t���O���Z�b�g����֐�
	{
		m_start = start_f;
	}
	bool GetDeath_f()					 //���������񂾂��ǂ����̃t���O���Q�b�g����֐�
	{
		return death_f;
	}

	void SetDeath_f(bool flag)			 //���������񂾂��ǂ����̃t���O���Z�b�g����֐�
	{
		death_f = flag;
	}

	bool Getstop_f()					 //��~�t���O���Q�b�g����֐�
	{
		return stop_f;
	}

	void Setstop_f(bool flag)			 //��~�t���O���Z�b�g����֐�
	{
		stop_f = flag;
	}
	void AddDeleteGOListeners(std::function<void(GameObject*)> listener)
	{
		m_deleteGoListeners.push_back(listener);
	}
	//�폜���Ď����Ă��郊�X�i�[�ɍ폜�����ꂽ���Ƃ�ʒm
	void NotifyDeleteGOListeners()
	{
		for (auto listener : m_deleteGoListeners) {
			listener(this);
		}
	}
private:
	const char* this_name;				//���O
	bool m_start = false;				//�X�^�[�g�t���O
	bool death_f = false;				//���S�t���O(���̌㎀��)
	bool stop_f = false;				//��~�t���O
	std::list<std::function<void(GameObject*)>>	m_deleteGoListeners;		//�폜�C�x���g�̃��X�i�[�B
};

