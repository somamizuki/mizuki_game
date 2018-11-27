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
	for (auto& deleteobj : deletelist)
	{
		for (auto& obj_list : GameObject_list)
		{
			for (auto& obj : obj_list)
			{
				if (deleteobj == obj)
				{
					delete obj;
					obj_list.erase(std::find(obj_list.begin(), obj_list.end(),obj));
					break;
				}
			}
		}
	}
	deletelist.clear();
	
	for (auto& obj_list : GameObject_list)				
	{
		for (auto& obj : obj_list)
		{
			if (obj != nullptr)
			{

				if (obj->Get_isStart() == false)
				{
					if (obj->Start())
					{
						obj->Set_isStart(true);
					}
				}
				if (!obj->GetDeath_f()&&!obj->Getstop_f()) obj->Update();
				
				
			}
		}
	}
	for (auto& obj_list : GameObject_list)
	{
		for (const auto& obj : obj_list)
		{
			if (obj != nullptr) 
			{
				if (obj->Get_isStart() == true)
				{
					if (!obj->GetDeath_f()) obj->Draw();
				}
			}
		}
	}

	for (auto& obj_list : GameObject_list)
	{
		for (const auto& obj : obj_list)
		{
			if (obj != nullptr)
			{
				if (obj->Get_isStart() == true)
				{
					if (!obj->GetDeath_f()) obj->PostDraw();
				}
			}
		}
	}

	for (auto& obj_list : GameObject_list)
	{
		for (const auto& obj : obj_list)
		{
			if (obj != nullptr)
			{
				if (obj->Get_isStart() == true)
				{
					if (!obj->GetDeath_f()) obj->UIDraw();
				}
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
				obj->SetDeath_f(true);
				deletelist.push_back(obj);
				break;
			}
		}
	}
}