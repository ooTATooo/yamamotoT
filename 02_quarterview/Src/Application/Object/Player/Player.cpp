#include "Player.h"

void Player::Update()
{
	m_dir = Math::Vector3::Zero;

	if (GetAsyncKeyState(VK_UP) & 0x8000) { m_dir += { 0, 0, 1 }; }
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { m_dir += { 0, 0, -1 }; }
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { m_dir += { -1, 0, 0 }; }
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { m_dir += { 1, 0, 0 }; }

	m_dir.Normalize();

	m_pos += m_dir * m_spped;

	// 重力をキャラに反映
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;

	m_poly->SetUVRect(12);


	//======================================
	// 当たり判定		レイ判定	ここから
	//======================================

	// レイ判定用に必要パラメータを設定する構造体を宣言
	KdCollider::RayInfo rayinfo;

	// レイの発射位置(座標)を設定
	rayinfo.m_pos = m_pos;

	// 少し高いところから飛ばす
	rayinfo.m_pos.y += 0.1f;

	// レイの方向を設定
	rayinfo.m_dir = { 0.0f,-1.0f,0.0f };

	// レイの長さを確定
	rayinfo.m_range = m_gravity;

	// 当たり判定をしたいタイプを設定
	rayinfo.m_type = KdCollider::TypeGround;

	//======================================
	// 当たり判定		レイ判定	ここまで
	//======================================
}

void Player::PostUpdate()
{
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void Player::Init()
{
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/Player.png");
	m_poly->SetSplit(4, 8);
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_pos = m_mWorld.Translation();
	m_spped = 0.1f;
	m_gravity = 0.0f;
	m_mWorld = Math::Matrix::Identity;
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}
