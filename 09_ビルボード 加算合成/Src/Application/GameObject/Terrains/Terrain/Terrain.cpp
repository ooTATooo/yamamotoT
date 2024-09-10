#include "Terrain.h"

void Terrain::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Terrains/Terrain/Terrain.gltf");

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("Ground", m_spModel, KdCollider::TypeGround|KdCollider::TypeDamage);
	}
}

void Terrain::DrawLit()
{
	if (!m_spModel) return;

	Math::Matrix scaleMat = Math::Matrix::CreateScale(3);
	m_mWorld = scaleMat;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel,m_mWorld);
}

