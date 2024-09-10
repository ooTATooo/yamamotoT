#include "WeaponBase .h"

void WeaponBase::Update()
{
	Math::Matrix parentMat;
	//const std::shared_ptr<const KdGameObject> _spParent = m_wpParent.lock();
	//コンスト大切
	
	if (!m_wpParent.expired())
	{
		//親の行列を取得
		 parentMat= m_wpParent.lock()->GetMatrix();

		 Math::Matrix _transMat = Math::Matrix::CreateTranslation({ 0.35f,-0.25f,0.2f });

		 m_mWorld = m_localMat  * parentMat;

	}
}

void WeaponBase::DrawLit()
{
	if (!m_spModel)return;
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
