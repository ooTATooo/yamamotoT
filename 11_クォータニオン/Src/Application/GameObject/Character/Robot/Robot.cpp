#include "Robot.h"

void Robot::Init()
{
	m_spModel = std::make_shared<KdModelWork>();
	m_spModel->SetModelData("Asset/Models/Character/Robot/Robot.gltf");

	// オブジェクト名
	m_objName = "Robot";

	// カメラのローカル行列
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0, 5.0f, -5.0f);
	Math::Matrix rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_mLocalCamera = rotMat * transMat;
}

void Robot::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}
