#include "stdafx.h"
//#include "GameObject.h"
GameObject::GameObject(int No,  const char* obj_name)
{
	game_obj->Set_push_list(this, No);		//���g���I�u�W�F�N�g���X�g�ɐς�ł���
	this_name = obj_name;					//���O���Z�b�g���Ă���
}