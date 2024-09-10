#include "WoodenBox.h"

void WoodenBox::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Terrains/WoodenBox/Wooden_Box.gltf");

		m_pCollider = std::make_unique<KdCollider>();
		m_pCollider->RegisterCollisionShape("Ground", m_spModel, KdCollider::TypeGround);
	

	}
}

void WoodenBox::DrawLit()
{
	if (!m_spModel) return;

	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix _scaleMat = Math::Matrix::CreateScale(10.f);
	m_mWorld = _scaleMat * _transMat;



	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

