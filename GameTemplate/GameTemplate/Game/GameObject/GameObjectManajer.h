#pragma once
//#include "GameObject.h"
class GameObjectManajer:Noncopyable
{
public:
	GameObjectManajer();
	~GameObjectManajer();

	void Set_push_list(GameObject* obj, int No)
	{
		GameObject_list[No].push_back(obj);
	}

	void DeleteGO(char *name);
	template<class T>
	void DeleteGO(T* obj_t)
	{
		for (auto& obj_list : GameObject_list)
		{
			for (auto& obj : obj_list)
			{
				if (obj == obj_t)
				{
					obj_list.erase(std::remove(obj_list.begin(), obj_list.end(), obj), obj_list.end());
					delete obj_t;
					break;
				}
			}
		}
	}
	template<class T>
	T* FindGO(char *name)
	{

		for (auto& obj_list : GameObject_list)
		{
			for (auto& obj : obj_list)
			{
				if (std::strcmp(name, obj->GetName())==0)
				{
					return (T*)obj;
				}
			}
		}
		return nullptr;
	}
	void Execute();
private:
	std::vector<std::list<GameObject*>> GameObject_list;

};

