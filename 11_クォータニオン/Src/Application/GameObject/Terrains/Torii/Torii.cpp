#include "Torii.h"

void Torii::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Terrains/Torii/Torii.gltf");
	}

	m_mWorld.Translation({ 100.0f, 0.0f, 100.0f });

	// オブジェクト名
	m_objName = "Torii";

	// カメラのローカル行列
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0, 10.0f, -10.0f);
	Math::Matrix rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_mLocalCamera = rotMat * transMat;

}

void Torii::DrawLit()
{
	if (!m_spModel) return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
