#pragma once
class GameObject :Noncopyable
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="No">�D��x</param>
	/// <param name="obj_name">�I�u�W�F�N�g�̖��O</param>
	GameObject(int No, const char* obj_name);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~GameObject()
	{
		for (const auto& hasmypointobj : m_hasMyPointerlist)
		{
			delete hasmypointobj;
		}
		m_hasMyPointerlist.clear();
	}
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	virtual bool Start() { return true; }
	/// <summary>
	/// �A�b�v�f�[�g�֐�
	/// </summary>
	virtual void Update() {}
	/// <summary>
	/// �`��֐�
	/// </summary>
	virtual void Draw() {}
	/// <summary>
	/// �G�t�F�N�g�`��
	/// </summary>
	virtual void EffectDraw() {}
	/// <summary>
	/// ��O�ɕ`�悵�������̂̕`��
	/// </summary>
	virtual void PostDraw() {}
	/// <summary>
	/// UI�`��
	/// </summary>
	virtual void UIDraw() {}
	/// <summary>
	/// DeleteGO���ɌĂ΂��֐�
	/// </summary>
	virtual void OnDestroy() {}
	/// <summary>
	/// �N���X���̃Q�b�^�[
	/// </summary>
	/// <returns>���O(const char*)</returns>
	const char* GetName()
	{
		return this_name;
	}
	/// <summary>
	/// �X�^�[�g�t���O���Q�b�g����֐�
	/// </summary>
	/// <returns>�X�^�[�g�t���O(bool)</returns>
	bool Get_isStart()
	{
		return m_start;
	}
	/// <summary>
	/// �X�^�[�g�t���O���Z�b�g����֐�
	/// </summary>
	/// <param name="start_f">�X�^�[�g�t���O(bool)</param>
	void Set_isStart(bool start_f)
	{
		m_start = start_f;
	}
	/// <summary>
	/// ���������񂾂��ǂ����̃t���O���Q�b�g����֐�
	/// </summary>
	/// <returns>���S�t���O(bool)</returns>
	bool GetDeath_f()
	{
		return death_f;
	}
	/// <summary>
	/// ���������񂾂��ǂ����̃t���O���Z�b�g����֐�
	/// </summary>
	/// <param name="flag">���S�t���O(bool)</param>
	void SetDeath_f(bool flag)
	{
		death_f = flag;
	}
	/// <summary>
	/// ��~�t���O���Q�b�g����֐�
	/// </summary>
	/// <returns>��~�t���O(bool)</returns>
	bool Getstop_f()
	{
		return stop_f;
	}
	/// <summary>
	/// ��~�t���O���Z�b�g����֐�
	/// </summary>
	/// <param name="flag">��~�t���O(bool)</param>
	void Setstop_f(bool flag)
	{
		stop_f = flag;
	}

	template<class T, class C>
	/// <summary>
	/// �����������|�C���^�ւ̃|�C���^�Ƃ�����������I�u�W�F�N�g�ւ̃|�C���^��o�^
	/// </summary>
	/// <param name="myPointer">&Delete����NULL�����Ăق����|�C���^</param>
	/// <param name="hasobject">this</param>
	void AddMyPointer(T** myPointer, C* hasobject)		//add�����Delete����NULL�����Ă����
	{
		hasMyPointerObject* s_hasMyPointerObject = new hasMyPointerObject;
		s_hasMyPointerObject->object = hasobject;
		s_hasMyPointerObject->m_MyPointer = (GameObject**)myPointer;

		m_hasMyPointerlist.push_back(s_hasMyPointerObject);
	}

	template<class T>
	/// <summary>
	/// �����œn���ꂽ�I�u�W�F�N�g�����X�g�ɂ���΍폜����
	/// </summary>
	/// <param name="obj">�I�u�W�F�N�g�ւ̃|�C���^�[</param>
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

	/// <summary>
	/// �����������|�C���^�ւ̃|�C���^�̒��g��nullptr����
	/// </summary>
	void NotifyDeleteGOtoHasMyPointerObject()
	{
		for (const auto& mypointer : m_hasMyPointerlist)
		{
			*mypointer->m_MyPointer = nullptr;
			delete mypointer;
		}
		m_hasMyPointerlist.clear();
	}
private:

	const char* this_name;				//���O
	bool m_start = false;				//�X�^�[�g�t���O
	bool death_f = false;				//���S�t���O(���̌㎀��)
	bool stop_f = false;				//��~�t���O
	/*�����������|�C���^�ւ̃|�C���^�Ƃ�����������I�u�W�F�N�g�ւ̃|�C���^�����\����*/
	struct hasMyPointerObject
	{
		GameObject* object;
		GameObject** m_MyPointer;
	};
	/*�����������|�C���^�ւ̃|�C���^�Ƃ�����������I�u�W�F�N�g�ւ̃|�C���^�����\���̂̃��X�g*/
	std::list<hasMyPointerObject*> m_hasMyPointerlist;
};

