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
	/*deletelistに登録されたオブジェクトを削除*/
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
	//deletelistの要素を削除
	deletelist.clear();
	
	//更新処理。ついでにスタート関数も呼んでいる
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
	/*通常描画*/
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
	/*ポスト描画*/
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
	/*UIなど、一番前に描画したいものの描画*/
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