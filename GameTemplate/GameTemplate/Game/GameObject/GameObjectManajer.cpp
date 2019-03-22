#include "stdafx.h"
#include "GameObjectManajer.h"


GameObjectManajer::GameObjectManajer()
{
	GameObject_list.resize(3);
}


GameObjectManajer::~GameObjectManajer()
{

	for (const auto& obj_list : GameObject_list)
	{
		for (const auto& obj : obj_list)
		{
			if (obj->GetName() != "game")
			{
				delete obj;
			}
		}
	}

}

void GameObjectManajer::Execute()
{
	/*deletelist�ɓo�^���ꂽ�I�u�W�F�N�g���폜*/
	for (const auto& deleteobj : deletelist)
	{
		for (auto& obj_list : GameObject_list)
		{
			for (const auto& obj : obj_list)
			{
				if (deleteobj == obj)
				{
					delete obj;
					obj_list.erase(std::remove(obj_list.begin(), obj_list.end(), obj), obj_list.end());
					break;
				}
			}
		}
	}
	//deletelist�̗v�f���폜
	deletelist.clear();

	//�X�V�����B���łɃX�^�[�g�֐����Ă�ł���
	for (const auto& obj_list : GameObject_list)
	{
		for (const auto& obj : obj_list)
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
			}
		}
	}

	for (const auto& obj_list : GameObject_list)
	{
		for (const auto& obj : obj_list)
		{
			if (obj != nullptr)
			{
				if (!obj->GetDeath_f() && !obj->Getstop_f() && obj->Get_isStart()) obj->Update();
			}
		}
	}
	/*�V���h�E�L���X�^�[�ɓo�^���ꂽ���f�����V���h�E�}�b�v�p�̃����_�����O�^�[�Q�b�g�ɕ`��*/
	if (g_graphicsEngine->GetShadowMap() != nullptr)
	{
		ShadowMap* shadowMap = g_graphicsEngine->GetShadowMap();
		shadowMap->ShadowMapDraw();
	}
	g_graphicsEngine->ChangeRenderTarget(g_graphicsEngine->GetmainRenderTarget(), g_graphicsEngine->GetmainViewport());
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	g_graphicsEngine->GetmainRenderTarget()->ClearRenderTarget(clearColor);
	/*�ʏ�`��*/
	for (const auto& obj_list : GameObject_list)
	{
		for (const auto& obj : obj_list)
		{
			if (obj != nullptr)
			{
				if (!obj->GetDeath_f() && obj->Get_isStart() == true)
				{
					obj->Draw();
				}
			}
		}
	}
	for (const auto& obj_list : GameObject_list)
	{
		for (const auto& obj : obj_list)
		{
			if (obj != nullptr)
			{
				if (!obj->GetDeath_f() && obj->Get_isStart() == true)
				{
					obj->EffectDraw();
				}
			}
		}
	}
	g_graphicsEngine->GetBloom()->Update();


	/*�|�X�g�`��*/
	for (const auto& obj_list : GameObject_list)
	{
		for (const auto& obj : obj_list)
		{
			if (obj != nullptr)
			{
				if (!obj->GetDeath_f() && obj->Get_isStart() == true)
				{
					obj->PostDraw();
				}
			}
		}
	}

	/*UI�ȂǁA��ԑO�ɕ`�悵�������̂̕`��*/
	for (const auto& obj_list : GameObject_list)
	{
		for (const auto& obj : obj_list)
		{
			if (obj != nullptr)
			{
				if (!obj->GetDeath_f() && obj->Get_isStart() == true)
				{
					obj->UIDraw();
				}
			}
		}
	}
	g_graphicsEngine->ReSetRenderTarget();

}

void GameObjectManajer::DeleteGO(char *name)
{
	for (const auto& obj_list : GameObject_list)
	{
		for (const auto& obj : obj_list)
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