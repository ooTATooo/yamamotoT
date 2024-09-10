#include "WoodenBox.h"

void WoodenBox::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Terrains/WoodenBox/Wooden_Box.gltf");

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("Box", m_spModel, KdCollider::TypeGround|KdCollider::TypeDamage);
	}
}

void WoodenBox::DrawLit()
{
	if (!m_spModel) return;

	Math::Matrix scaleMat = Math::Matrix::CreateScale(10);
	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_mWorld.Translation());
	m_mWorld = scaleMat * transMat;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
