#pragma once
#include "GameObject.h"
class GameObjectManajer:Noncopyable
{
public:
	GameObjectManajer();
	~GameObjectManajer();

	void Set_push_list(GameObject* obj, int No)				//オブジェクトのリストにプッシュする関数
	{
		GameObject_list[No].push_back(obj);
	}
	void DeleteGO(char *name);								//オブジェクトを名前で削除するクラス
	template<class T>
	void DeleteGO(T* obj_t)									//オブジェクトをポインターで削除するクラス
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
					//リスナーに削除されたことを通知する。
					//obj->NotifyDeleteGOListeners();
					obj->NotifyDeleteGOtoHasMyPointerObject();
					deletelist.push_back(obj);
					break;
				}
			}
		}
	}
	template<class T>
	T* FindGO(char *name)									//オブジェクトを名前で見つけるクラス
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
	T* FindGO(T* obj_t)										//オブジェクトをポインターで見つけるクラス
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
	void allStop(GameObject* object)						//引数で渡されたオブジェクト以外全ての更新をスキップ
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
	void alltomarunjanee()								//全ての更新を再開
	{
		for (const auto& objlist : GameObject_list)
		{
			for (const auto& obj : objlist)
			{
				obj->Setstop_f(false);
			}
		}
	}

	void Execute();							//更新関数
private:
	std::vector<std::list<GameObject*>> GameObject_list;	//オブジェクトリスト
	std::list<GameObject*> deletelist;						//デリートリスト
};

