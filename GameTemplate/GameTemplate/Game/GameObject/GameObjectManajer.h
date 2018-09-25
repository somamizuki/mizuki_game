#pragma once
#include "GameObject.h"
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
	T* FindGO(char *name)
	{
		for (auto& obj_list : GameObject_list)
		{
			for (auto obj : obj_list)
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

