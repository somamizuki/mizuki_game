#include "stdafx.h"
//#include "GameObject.h"
GameObject::GameObject(int No,  const char* obj_name)
{
	game_obj->Set_push_list(this, No);		//自身をオブジェクトリストに積んでいる
	this_name = obj_name;					//名前をセットしている
}