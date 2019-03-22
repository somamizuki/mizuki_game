#pragma once
#include "GameObject.h"
class GameObjectManajer:Noncopyable
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameObjectManajer();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameObjectManajer();
	/// <summary>
	/// オブジェクトのリストにプッシュする関数
	/// </summary>
	/// <param name="obj">オブジェクトのポインター</param>
	/// <param name="No">優先度</param>
	void Set_push_list(GameObject* obj, int No)
	{
		GameObject_list[No].push_back(obj);
	}
	/// <summary>
	/// オブジェクトを名前で削除する関数
	/// </summary>
	void DeleteGO(char *name);
	template<class T>
	/// <summary>
	/// オブジェクトをポインターで削除する関数
	/// </summary>
	/// <param name="obj_t">オブジェクトへのポインター</param>
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
	/// オブジェクトを名前で見つける関数
	/// </summary>
	/// <param name="name">名前</param>
	/// <returns>オブジェクトへのポインター</returns>
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
	/// <summary>
	/// いらない。なぜつくったんだろう。
	/// </summary>
	/// <param name="obj_t"></param>
	/// <returns></returns>
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
	/// <summary>
	/// 引数で渡されたオブジェクト以外全ての更新をスキップ
	///	デバッグ用
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
	/// 全ての更新を再開
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
	/// 更新関数
	/// </summary>
	void Execute();
private:
	std::vector<std::list<GameObject*>> GameObject_list;	//オブジェクトリスト
	std::list<GameObject*> deletelist;						//削除リスト
};

