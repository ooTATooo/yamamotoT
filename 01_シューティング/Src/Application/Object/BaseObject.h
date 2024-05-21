﻿#pragma once

class BaseObject
{
public:

	BaseObject() {}
	virtual ~BaseObject() {}

	// オブジェクトの種類
	enum class ObjectType
	{
		Player,
		Enemy,
		Bullet,
	};

	//仮想関数
	virtual void Update();
	virtual void Draw();
	virtual void Init();
	virtual void Release();

	void SetTexture(std::string _fileName);

	ObjectType GetObjType() { return m_objType; }

	Math::Vector3 GetPos() { return m_pos; }

	bool GetAliveFlg() { return m_aliveFlg; }

	// Hit時の処理
	virtual void OnHit();

protected:

	KdTexture m_tex;
	Math::Vector3 m_pos;
	Math::Matrix m_mat;

	bool m_aliveFlg = true;

	ObjectType m_objType;

private:


};