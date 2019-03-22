#pragma once
#include "GameObject.h"
class GameObjectManajer:Noncopyable
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameObjectManajer();
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameObjectManajer();
	/// <summary>
	/// �I�u�W�F�N�g�̃��X�g�Ƀv�b�V������֐�
	/// </summary>
	/// <param name="obj">�I�u�W�F�N�g�̃|�C���^�[</param>
	/// <param name="No">�D��x</param>
	void Set_push_list(GameObject* obj, int No)
	{
		GameObject_list[No].push_back(obj);
	}
	/// <summary>
	/// �I�u�W�F�N�g�𖼑O�ō폜����֐�
	/// </summary>
	void DeleteGO(char *name);
	template<class T>
	/// <summary>
	/// �I�u�W�F�N�g���|�C���^�[�ō폜����֐�
	/// </summary>
	/// <param name="obj_t">�I�u�W�F�N�g�ւ̃|�C���^�[</param>
	void DeleteGO(T* obj_t)
	{
		for (const auto& deleteobj : deletelist)
		{
			if (obj_t == deleteobj)
			{
				return;
			}
		}

		for (const auto& obj_list : GameObject_list)
		{
			for (const auto& obj : obj_list) 
			{
				obj->RemoveHasMyPointerObject<T>(obj_t);
			}
		}
		
		for (const auto& obj_list : GameObject_list)
		{
			for (const auto& obj : obj_list)
			{
				if (obj == obj_t)
				{
					obj->SetDeath_f(true);
					obj->OnDestroy();
					obj->NotifyDeleteGOtoHasMyPointerObject();
					deletelist.push_back(obj);
					break;
				}
			}
		}
	}
	template<class T>
	/// <summary>
	/// �I�u�W�F�N�g�𖼑O�Ō�����֐�
	/// </summary>
	/// <param name="name">���O</param>
	/// <returns>�I�u�W�F�N�g�ւ̃|�C���^�[</returns>
	T* FindGO(char *name)									//�I�u�W�F�N�g�𖼑O�Ō�����N���X
	{
		for (const auto& obj_list : GameObject_list)
		{
			for (const auto& obj : obj_list)
			{
				if (!(std::strcmp(name, obj->GetName())))
				{
					return (T*)obj;
				}
			}
		}
		return nullptr;
	}

	template<class T>
	/// <summary>
	/// ����Ȃ��B�Ȃ��������񂾂낤�B
	/// </summary>
	/// <param name="obj_t"></param>
	/// <returns></returns>
	T* FindGO(T* obj_t)										//�I�u�W�F�N�g���|�C���^�[�Ō�����N���X
	{
		for (const auto& obj_list : GameObject_list)
		{
			for (const auto& obj : obj_list)
			{
				if (obj== obj_t)
				{
					return (T*)obj;
				}
			}
		}
		return nullptr;
	}
	/// <summary>
	/// �����œn���ꂽ�I�u�W�F�N�g�ȊO�S�Ă̍X�V���X�L�b�v
	///	�f�o�b�O�p
	/// </summary>
	/// <param name="object"></param>
	void allStop(GameObject* object)
	{
		for (const auto& objlist : GameObject_list)
		{
			for (const auto& obj : objlist)
			{
				if (obj != object)
				{
					obj->Setstop_f(true);
				}
			}
		}
	}
	/// <summary>
	/// �S�Ă̍X�V���ĊJ
	/// </summary>
	void alltomarunjanee()
	{
		for (const auto& objlist : GameObject_list)
		{
			for (const auto& obj : objlist)
			{
				obj->Setstop_f(false);
			}
		}
	}
	/// <summary>
	/// �X�V�֐�
	/// </summary>
	void Execute();
private:
	std::vector<std::list<GameObject*>> GameObject_list;	//�I�u�W�F�N�g���X�g
	std::list<GameObject*> deletelist;						//�폜���X�g
};

