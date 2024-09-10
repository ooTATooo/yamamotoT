#include "Lift.h"

void Lift::Update()
{
	m_degAng++;
	if (m_degAng > 360.0f)
	{
		m_degAng = 0;
	}

	m_pos.x = sin(DirectX::XMConvertToRadians(m_degAng)) * m_moveVal;

	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void Lift::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Terrains/Lift/Lift.gltf");

		m_pos = { 0,10.0f,30.0f };

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("Lift", m_spModel, KdCollider::TypeGround);
	}
}

void Lift::DrawLit()
{
	if (!m_spModel)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
