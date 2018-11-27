#pragma once
#include"Player.h"
#include"Class_of_NewGO.h"
#include"bulletinfo.h"

using namespace BulletInfo;
class bullet:public GameObject
{
public:
	bullet(int No, const char* obj_name);
	~bullet();

	bool Start();									//スタート関数(初期化とか)
	void Update();									//更新処理
	void Draw();									//描画

	const CVector3 Getpos() const					//ポジションをあげる関数
	{
		return bulletpos;
	}

private:
	//たま
	SkinModel m_tama;								//玉のモデル
	CVector3 tamadir = CVector3::Zero();			//玉のディレクション
	CVector3 bulletpos = CVector3::Zero();			//玉のポジション
	float speed = 0.0f;								//玉の最終速度
	Player* m_player = nullptr;						//プレイヤーのポインター
	Class_of_NewGO* CoN = nullptr;					//いろんなクラスをnewするクラスのポインター
};

