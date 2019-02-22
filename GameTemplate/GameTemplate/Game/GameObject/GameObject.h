#pragma once
//#include "GameObjectManajer.h"
class GameObject:Noncopyable
{
public:
	//優先度,オブジェクトの名前
	GameObject(int No, const char* obj_name);
	//{
	//	game_obj.Set_push_list(this, No);
	//	this_name = obj_name;
	//}
	virtual ~GameObject()
	{

	}
	virtual bool Start() { return true; }//スタート関数(初期化とか)
	virtual void Update(){}				 //更新処理
	virtual void Draw(){}				 //描画
	virtual void EffectDraw(){}			 //エフェクトの描画
	virtual void PostDraw(){}			 //手前に描画したいものの描画
	virtual void UIDraw() {}			 //UIとかの描画
	virtual void OnDestroy(){}			 //オンデストロイ
	const char* GetName()				 //クラス名のゲッター
	{
		return this_name;
	}
	bool Get_isStart()					 //スタートフラグをゲットする関数
	{
		return m_start;
	}
	void Set_isStart(bool start_f)		 //スタートフラグをセットする関数
	{
		m_start = start_f;
	}
	bool GetDeath_f()					 //自分が死んだかどうかのフラグをゲットする関数
	{
		return death_f;
	}

	void SetDeath_f(bool flag)			 //自分が死んだかどうかのフラグをセットする関数
	{
		death_f = flag;
	}

	bool Getstop_f()					 //停止フラグをゲットする関数
	{
		return stop_f;
	}

	void Setstop_f(bool flag)			 //停止フラグをセットする関数
	{
		stop_f = flag;
	}
	/*void AddDeleteGOListeners(std::function<void(GameObject*)> listener)
	{
		m_deleteGoListeners.push_back(listener);
	}*/
	//削除を監視しているリスナーに削除をされたことを通知
	/*void NotifyDeleteGOListeners()
	{
		for (auto listener : m_deleteGoListeners) {
			listener(this);
		}
	}*/
	template<class T,class C>
	void AddMyPointer(T** myPointer,C* hasobject)
	{
		hasMyPointerObject* s_hasMyPointerObject = new hasMyPointerObject;
		s_hasMyPointerObject->object = hasobject;
		s_hasMyPointerObject->m_MyPointer = (GameObject**)myPointer;

		m_hasMyPointerlist.push_back(s_hasMyPointerObject);
	}
	template<class T>
	void RemoveHasMyPointerObject(T* obj)
	{
		for (auto& mypointer : m_hasMyPointerlist)
		{
			if (obj == mypointer->object)
			{
				m_hasMyPointerlist.erase(std::remove(m_hasMyPointerlist.begin(), m_hasMyPointerlist.end(), mypointer), m_hasMyPointerlist.end());
				break;
			}
		}
	}
	void NotifyDeleteGOtoHasMyPointerObject()
	{
		for (auto& mypointer : m_hasMyPointerlist)
		{
			*mypointer->m_MyPointer = nullptr;
		}
	}
private:
	const char* this_name;				//名前
	bool m_start = false;				//スタートフラグ
	bool death_f = false;				//死亡フラグ(この後死ぬ)
	bool stop_f = false;				//停止フラグ
	//std::list<std::function<void(GameObject*)>>	m_deleteGoListeners;		//削除イベントのリスナー。
	struct hasMyPointerObject
	{
		GameObject* object;
		GameObject** m_MyPointer;
	};
	std::list<hasMyPointerObject*> m_hasMyPointerlist;
};

