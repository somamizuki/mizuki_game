#include "stdafx.h"
#include "bullet.h"



bullet::bullet(int No, const char* obj_name) : GameObject(No, obj_name)
{
}


bullet::~bullet()
{

}

bool bullet::Start()
{
	
	m_tama.Init(L"Assets/modelData/kyutai.cmo");					//玉のモデルイニット
	m_player = game_obj->FindGO<Player>("player");					//プレイヤーの検索
	CoN = game_obj->FindGO<Class_of_NewGO>("newObject");			//いろんなクラスをnewするクラスを検索
	tamadir = m_player->Getforward();								//玉のディレクションにプレイヤーのフォワードを代入
	speed = m_player->Get_PlayerMove().Length()+bulletspeed;		//玉の最終スピード
	bulletpos = m_player->Getpos() + tamadir *500.0f;				//バレットのポジションをプレイヤーの前方500の位置にセット
	return true;
}

void bullet::Update()
{
	bulletpos += tamadir * (speed*(1.0f / 60.0f));					//バレットを進めている
	CVector3 e_to_b = CVector3::Zero();								//エネミーからバレットへのベクトル
	if (!this->GetDeath_f())										//自分の死亡フラグがたっていなければ
	{
		if (!CoN->GetDeath_f())										//いろんなクラスをnewするクラスの死亡フラグがたっていなければ
		{
			for (auto& enemy : CoN->GetEnemy())
			{
				e_to_b = bulletpos - enemy->Getpos();				//エネミーからバレットへのベクトルを求める
				if (e_to_b.Length() < 300.0f)						//e_to_bの長さが300.0f未満なら
				{
					game_obj->DeleteGO(enemy);						//条件に合ったエネミーの死亡フラグをたてる
					CoN->GetEnemy().erase(std::remove(				//CoNのエネミーリストの要素を消す(イレースリムーブイデオム)
						CoN->GetEnemy().begin(),					//こっち側で消すという謎処理
						CoN->GetEnemy().end(), enemy),
						CoN->GetEnemy().end());
					game_obj->DeleteGO(this);						//エネミーと当たったので自分を消す
				}
			}
		}
		
	}
	
	m_tama.UpdateWorldMatrix(bulletpos, CQuaternion::Identity(), { 0.05f,0.05f,0.05f });		//ワールドマトリクスの更新
}

void bullet::Draw()
{
	m_tama.Draw(																				//玉の描画
		1,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}