#include "Player.h"

void Player::Update()
{
	m_poly->SetUVRect(12);

	m_dir = Math::Vector3::Zero;

	if (GetAsyncKeyState(VK_UP) & 0x8000) { m_dir += { 0, 0, 1 }; }
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { m_dir += { 0, 0, -1 }; }
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { m_dir += { -1, 0, 0 }; }
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { m_dir += { 1, 0, 0 }; }

	m_dir.Normalize();
	m_pos += m_dir * m_spped;
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
