#pragma once
class GameObject :Noncopyable
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="No">優先度</param>
	/// <param name="obj_name">オブジェクトの名前</param>
	GameObject(int No, const char* obj_name);
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~GameObject()
	{
		for (const auto& hasmypointobj : m_hasMyPointerlist)
		{
			delete hasmypointobj;
		}
		m_hasMyPointerlist.clear();
	}
	/// <summary>
	/// スタート関数
	/// </summary>
	virtual bool Start() { return true; }
	/// <summary>
	/// アップデート関数
	/// </summary>
	virtual void Update() {}
	/// <summary>
	/// 描画関数
	/// </summary>
	virtual void Draw() {}
	/// <summary>
	/// エフェクト描画
	/// </summary>
	virtual void EffectDraw() {}
	/// <summary>
	/// 手前に描画したいものの描画
	/// </summary>
	virtual void PostDraw() {}
	/// <summary>
	/// UI描画
	/// </summary>
	virtual void UIDraw() {}
	/// <summary>
	/// DeleteGO時に呼ばれる関数
	/// </summary>
	virtual void OnDestroy() {}
	/// <summary>
	/// クラス名のゲッター
	/// </summary>
	/// <returns>名前(const char*)</returns>
	const char* GetName()
	{
		return this_name;
	}
	/// <summary>
	/// スタートフラグをゲットする関数
	/// </summary>
	/// <returns>スタートフラグ(bool)</returns>
	bool Get_isStart()
	{
		return m_start;
	}
	/// <summary>
	/// スタートフラグをセットする関数
	/// </summary>
	/// <param name="start_f">スタートフラグ(bool)</param>
	void Set_isStart(bool start_f)
	{
		m_start = start_f;
	}
	/// <summary>
	/// 自分が死んだかどうかのフラグをゲットする関数
	/// </summary>
	/// <returns>死亡フラグ(bool)</returns>
	bool GetDeath_f()
	{
		return death_f;
	}
	/// <summary>
	/// 自分が死んだかどうかのフラグをセットする関数
	/// </summary>
	/// <param name="flag">死亡フラグ(bool)</param>
	void SetDeath_f(bool flag)
	{
		death_f = flag;
	}
	/// <summary>
	/// 停止フラグをゲットする関数
	/// </summary>
	/// <returns>停止フラグ(bool)</returns>
	bool Getstop_f()
	{
		return stop_f;
	}
	/// <summary>
	/// 停止フラグをセットする関数
	/// </summary>
	/// <param name="flag">停止フラグ(bool)</param>
	void Setstop_f(bool flag)
	{
		stop_f = flag;
	}

	template<class T, class C>
	/// <summary>
	/// 自分をさすポインタへのポインタとそれを持ったオブジェクトへのポインタを登録
	/// </summary>
	/// <param name="myPointer">&Delete時にNULLを入れてほしいポインタ</param>
	/// <param name="hasobject">this</param>
	void AddMyPointer(T** myPointer, C* hasobject)		//addするとDelete時にNULLを入れてくれる
	{
		hasMyPointerObject* s_hasMyPointerObject = new hasMyPointerObject;
		s_hasMyPointerObject->object = hasobject;
		s_hasMyPointerObject->m_MyPointer = (GameObject**)myPointer;

		m_hasMyPointerlist.push_back(s_hasMyPointerObject);
	}

	template<class T>
	/// <summary>
	/// 引数で渡されたオブジェクトがリストにあれば削除する
	/// </summary>
	/// <param name="obj">オブジェクトへのポインター</param>
	void RemoveHasMyPointerObject(T* obj)
	{
		for (const auto& mypointer : m_hasMyPointerlist)
		{
			if (obj == mypointer->object)
			{
				delete mypointer;
				m_hasMyPointerlist.erase(std::remove(m_hasMyPointerlist.begin(), m_hasMyPointerlist.end(), mypointer), m_hasMyPointerlist.end());
				break;
			}
		}
	}

	/// <summary>
	/// 自分をさすポインタへのポインタの中身にnullptrを代入
	/// </summary>
	void NotifyDeleteGOtoHasMyPointerObject()
	{
		for (const auto& mypointer : m_hasMyPointerlist)
		{
			*mypointer->m_MyPointer = nullptr;
			delete mypointer;
		}
		m_hasMyPointerlist.clear();
	}
private:

	const char* this_name;				//名前
	bool m_start = false;				//スタートフラグ
	bool death_f = false;				//死亡フラグ(この後死ぬ)
	bool stop_f = false;				//停止フラグ
	/*自分をさすポインタへのポインタとそれを持ったオブジェクトへのポインタを持つ構造体*/
	struct hasMyPointerObject
	{
		GameObject* object;
		GameObject** m_MyPointer;
	};
	/*自分をさすポインタへのポインタとそれを持ったオブジェクトへのポインタを持つ構造体のリスト*/
	std::list<hasMyPointerObject*> m_hasMyPointerlist;
};

