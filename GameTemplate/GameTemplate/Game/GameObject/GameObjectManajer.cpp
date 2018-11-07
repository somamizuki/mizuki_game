#include "stdafx.h"
//#include "GameObjectManajer.h"


GameObjectManajer::GameObjectManajer()
{
	GameObject_list.resize(10);
}


GameObjectManajer::~GameObjectManajer()
{
}

void GameObjectManajer::Execute()
{
	for (auto& obj_list : GameObject_list)				
	{
		for (const auto& obj : obj_list)
		{
			if (obj->Get_isStart()==false)
			{
				if (obj->Start())
				{
					obj->Set_isStart(true);
				}
			}
			obj->Update();

		}
	}
	for (auto& obj_list : GameObject_list)
	{
		for (const auto& obj : obj_list)
		{
			if (obj->Get_isStart() == true)
			{
				
				obj->Draw();
			}
			
		}
	}
}

void GameObjectManajer::DeleteGO(char *name)
{
	for (auto& obj_list : GameObject_list)
	{
		for (auto& obj : obj_list)
		{
			if (std::strcmp(name, obj->GetName()))
			{
				obj_list.erase(std::remove(obj_list.begin(), obj_list.end(), obj), obj_list.end());
				delete obj;
				break;
			}
		}
	}
}