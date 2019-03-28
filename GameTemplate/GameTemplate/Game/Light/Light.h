#pragma once
#include "stdafx.h"
namespace Light {
	/// <summary>
	/// �f�B���N�V�������C�g�̍\����
	/// </summary>
	struct SDirectionLight {
		CVector4 color;
		CVector4 Direction;
	};
	/// <summary>
	/// �|�C���g���C�g�̍\����
	/// </summary>
	struct SPointLight {
		CVector4 color;
		CVector4 position;
		float range;
	};
	/// <summary>
	/// �X�|�b�g���C�g�̍\����
	/// </summary>
	struct SSpotLight {
		CVector4 color;
		CVector4 position;
		CVector4 Direction;
		float SpotAngle;				//���W�A���œ����B
		float range;
	};
	/// <summary>
	/// ���C�g�̃p�����[�^�[
	/// </summary>
	struct ligParam {
		CVector4 eyepos;
		float specPow;
	};
	/// <summary>
	/// ���C�g�̃^�C�v
	/// </summary>
	enum LightType {
		nolig,
		Direction,
		Point,
		Spot,
	};
}