#include "Enemy.h"

void Enemy::Update()
{
	m_pos += m_movePow;

	if (m_pos.y < -360.0f - 32.0f) m_pos.y = 360.0f + 32.0f;

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mat = transMat;
}

void Enemy::Draw()
{
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);
	Math::Rectangle rc = { 0,0,64,64 };
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, 0, 0, &rc);
}

void Enemy::Init()
{
	m_tex.Load("Asset/Textures/enemy.png");
	m_pos = {};							// 座標初期化
	m_mat = Math::Matrix::Identity;		// 単位行列で初期化
	m_movePow = { 0,-2,0 };				// 移動力初期化
	m_objType = ObjectType::Enemy;		// 種類は「エネミー」

}

void Enemy::OnHit()
{
	m_aliveFlg = false;
}


void Enemy::Release()
{
}
