#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <math.h>
#include <vector>
#include <list>
#include <D3Dcompiler.h>
#include <Windows.h>
#include <d3d11.h>
#include <map>
#include <functional>
#include <algorithm>

#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

//DirectXTKのインクルードファイル。
#include "DirectXTK/Inc/Model.h"
#include "DirectXTK/Inc/Effects.h"	
#include "DirectXTK/Inc/CommonStates.h"
#include "DirectXTK/Inc/SpriteFont.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"

#include "physics/Physics.h"
#include "HID/Pad.h"

#include "math/Vector.h"
#include "math/Matrix.h"
#include "graphics/GraphicsEngine.h"

#include "graphics/SkinModel.h"
#include "graphics/Skeleton.h"

#include "graphics/animation/Animation.h"
#include "graphics/animation/AnimationClip.h"
#include "graphics/Camera.h"
#include "policy/Noncopyable.h"
#include "graphics/Shader.h"
#include "GameObject/GameObject.h"
#include "GameObject/GameObjectManajer.h"
#include "graphics/sprite.h"

extern GameObjectManajer *game_obj;
static wchar_t* char_to_wchar_t(char* name)
{
	char* CPmodel_name = name;
	size_t char_size = strlen(CPmodel_name) + 1;
	wchar_t *WPmodel_name = new wchar_t[char_size];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, WPmodel_name, char_size, CPmodel_name, _TRUNCATE);
	return WPmodel_name;
}

const float FRAME_BUFFER_W = 1920.0f;				//フレームバッファの幅。
const float FRAME_BUFFER_H = 1080.0f;				//フレームバッファの高さ。

static const int MAX_BONE = 512;	//!<ボーンの最大数。
