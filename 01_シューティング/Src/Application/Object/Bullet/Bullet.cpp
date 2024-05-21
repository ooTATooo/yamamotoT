#include "Bullet.h"
#include "../../Scene/GameScene.h"

void Bullet::Update()
{
	m_pos += m_movePow;

	for (auto& obj : m_owner->GetObjList())
	{
		// 自分自身は当たり判定しない
		if (obj->GetObjType() == ObjectType::Bullet || obj->GetObjType() == ObjectType::Player) continue;

		// 敵だったら当たり判定を行う
		if (obj->GetObjType() == ObjectType::Enemy)
		{
			// 対象座標 - 自分座標 = 対象へのベクトル
			Math::Vector3 v;
			v = obj->GetPos() - m_pos;

			// 球判定 ・・・ ベクトルの長さで判定
			if (v.Length() < 64.0f)
			{
				// Hit時の処理を行う
				obj->OnHit();
				OnHit();
			}
		}
	}

	if (m_pos.x < -640.0f || m_pos.x > 640.0f || m_pos.y < -360.0f || m_pos.y > 360.0f)
	{
		m_aliveFlg = false;
	}

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = transMat;
}

void Bullet::Draw()
{
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);
	Math::Rectangle rc = { 0,0,13,37 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, &rc);
}

void Bullet::Init()
{
	m_tex.Load("Asset/Textures/bullet.png");
	m_pos = {};
	m_mat = Math::Matrix::Identity;
	m_movePow = { 0,10,0 };
	m_aliveFlg = false;
	m_objType = ObjectType::Bullet;
}

void Bullet::Shot(Math::Vector3 _shotPos)
{
	m_aliveFlg = true;
	m_pos = _shotPos;
}

void Bullet::OnHit()
{
	m_aliveFlg = false;
}

void Bullet::Release()
{
}
