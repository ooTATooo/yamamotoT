#include "WeaponBase.h"

void WeaponBase::Update()
{
	const std::shared_ptr<const KdGameObject> parent = m_wpParent.lock();
	if (parent)
	{
		// 親の行列を取得
		Math::Matrix parentMat = parent->GetMatrix();

		// 親の行列を反映したワールド行列を作成
		m_mWorld = m_localMat * parentMat;
	}
}

void WeaponBase::DrawLit()
{
	if (!m_spModel)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
