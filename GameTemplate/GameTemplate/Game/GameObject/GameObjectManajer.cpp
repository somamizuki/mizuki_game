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
	/*deletelist�ɓo�^���ꂽ�I�u�W�F�N�g���폜*/
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
	//deletelist�̗v�f���폜
	deletelist.clear();
	
	//�X�V�����B���łɃX�^�[�g�֐����Ă�ł���
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
	/*�ʏ�`��*/
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
	/*�|�X�g�`��*/
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
	/*UI�ȂǁA��ԑO�ɕ`�悵�������̂̕`��*/
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