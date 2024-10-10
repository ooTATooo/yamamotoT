#include "Lift.h"

void Lift::Update()
{
	float _sin = sin(DirectX::XMConvertToRadians(m_angle));

	++m_angle;
	if (m_angle >= 360.0f)
	{
		m_angle -= 360.0f;
	}

	Math::Matrix _transMat = Math::Matrix::CreateTranslation(_sin * m_moveVal, 10.0f, 60.0f);
	
	Math::Matrix _rotMat = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

	m_mWorld = _rotMat * _transMat;
}

void Lift::Init()
{
	m_spModel = std::make_shared<KdModelWork>();
	m_spModel->SetModelData("Asset/Models/Terrains/Lift/Lift.gltf");

	// オブジェクト名
	m_objName = "Lift";

	// カメラのローカル行列
	Math::Matrix transMat = Math::Matrix::CreateTranslation(0, 15.0f, -15.0f);
	Math::Matrix rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(45));
	m_mLocalCamera = rotMat * transMat;
}

void Lift::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}