#pragma once
#include "GameObject.h"
class GameObjectManajer:Noncopyable
{
public:
	GameObjectManajer();
	~GameObjectManajer();

	void Set_push_list(GameObject* obj, int No)				//�I�u�W�F�N�g�̃��X�g�Ƀv�b�V������֐�
	{
		GameObject_list[No].push_back(obj);
	}
	void DeleteGO(char *name);								//�I�u�W�F�N�g�𖼑O�ō폜����N���X
	template<class T>
	void DeleteGO(T* obj_t)									//�I�u�W�F�N�g���|�C���^�[�ō폜����N���X
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
					//���X�i�[�ɍ폜���ꂽ���Ƃ�ʒm����B
					//obj->NotifyDeleteGOListeners();
					obj->NotifyDeleteGOtoHasMyPointerObject();
					deletelist.push_back(obj);
					break;
				}
			}
		}
	}
	template<class T>
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
	/*void QueryGOs(char* name, std::function<void(GameObject* go)> func)
	{
		for (auto& obj_list : GameObject_list)
		{
			for (auto& obj : obj_list)
			{
				if (!(std::strcmp(name, obj->GetName())))
				{
					func(obj);
				}
			}
		}
	}*/
	void allStop(GameObject* object)						//�����œn���ꂽ�I�u�W�F�N�g�ȊO�S�Ă̍X�V���X�L�b�v
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
	void alltomarunjanee()								//�S�Ă̍X�V���ĊJ
	{
		for (const auto& objlist : GameObject_list)
		{
			for (const auto& obj : objlist)
			{
				obj->Setstop_f(false);
			}
		}
	}

	void Execute();							//�X�V�֐�
private:
	std::vector<std::list<GameObject*>> GameObject_list;	//�I�u�W�F�N�g���X�g
	std::list<GameObject*> deletelist;						//�f���[�g���X�g
};

