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
		for (const auto& hasmypointobj : m_hasMyPointerlist)
		{
			delete hasmypointobj;
		}
	}
	virtual bool Start() { return true; }//�X�^�[�g�֐�(�������Ƃ�)
	virtual void Update(){}				 //�X�V����
	virtual void Draw(){}				 //�`��
	virtual void EffectDraw(){}			 //�G�t�F�N�g�̕`��
	virtual void PostDraw(){}			 //��O�ɕ`�悵�������̂̕`��
	virtual void UIDraw() {}			 //UI�Ƃ��̕`��
	virtual void OnDestroy(){}			 //�I���f�X�g���C
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
	/*void AddDeleteGOListeners(std::function<void(GameObject*)> listener)
	{
		m_deleteGoListeners.push_back(listener);
	}*/
	//�폜���Ď����Ă��郊�X�i�[�ɍ폜�����ꂽ���Ƃ�ʒm
	/*void NotifyDeleteGOListeners()
	{
		for (auto listener : m_deleteGoListeners) {
			listener(this);
		}
	}*/
	/*�����������|�C���^�ւ̃|�C���^�Ƃ�����������I�u�W�F�N�g�ւ̃|�C���^��o�^*/
	template<class T,class C>
	void AddMyPointer(T** myPointer,C* hasobject)
	{
		hasMyPointerObject* s_hasMyPointerObject = new hasMyPointerObject;
		s_hasMyPointerObject->object = hasobject;
		s_hasMyPointerObject->m_MyPointer = (GameObject**)myPointer;

		m_hasMyPointerlist.push_back(s_hasMyPointerObject);
	}
	/*�����œn���ꂽ�I�u�W�F�N�g�����X�g�ɂ���΍폜����*/
	template<class T>
	void RemoveHasMyPointerObject(T* obj)
	{
		for (const auto& mypointer : m_hasMyPointerlist)
		{
			if (obj == mypointer->object)
			{
				delete mypointer;
				m_hasMyPointerlist.erase(std::remove(m_hasMyPointerlist.begin(), m_hasMyPointerlist.end(), mypointer), m_hasMyPointerlist.end());
				break;
			}
		}
	}
	/*�����������|�C���^�ւ̃|�C���^�̒��g��nullptr����*/
	/*DeleteGO���ɌĂ΂��*/
	void NotifyDeleteGOtoHasMyPointerObject()
	{
		for (const auto& mypointer : m_hasMyPointerlist)
		{
			*mypointer->m_MyPointer = nullptr;
		}
	}
private:
	const char* this_name;				//���O
	bool m_start = false;				//�X�^�[�g�t���O
	bool death_f = false;				//���S�t���O(���̌㎀��)
	bool stop_f = false;				//��~�t���O
	//std::list<std::function<void(GameObject*)>>	m_deleteGoListeners;		//�폜�C�x���g�̃��X�i�[�B
	/*�����������|�C���^�ւ̃|�C���^�Ƃ�����������I�u�W�F�N�g�ւ̃|�C���^�����\����*/
	struct hasMyPointerObject
	{
		GameObject* object;
		GameObject** m_MyPointer;
	};
	/*�����������|�C���^�ւ̃|�C���^�Ƃ�����������I�u�W�F�N�g�ւ̃|�C���^�����\���̂̃��X�g*/
	std::list<hasMyPointerObject*> m_hasMyPointerlist;
};

