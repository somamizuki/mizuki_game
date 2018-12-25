#pragma once

#include "physics/PhysicsStaticObject.h"

class Level;
struct LevelObjectData;

/*!
* @brief	マップチップ。
*/
class MapChip {
public:
	/*!
	* @brief	コンストラクタ。
	*@param[in] objData			オブジェクト情報。
	*/
	MapChip(const LevelObjectData& objData);
	SkinModel* GetModel()
	{
		return &m_model;
	}
	/*!
	* @brief	描画。
	*/
	void Draw();
private:
	SkinModel m_model;		//!<モデル。
	PhysicsStaticObject m_physicsStaticObject;	//!<静的物理オブジェクト。
	
};