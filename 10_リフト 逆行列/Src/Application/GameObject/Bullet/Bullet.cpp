#include "Bullet.h"

void Bullet::Update()
{
	//座標更新
	m_pos += m_moveDir * m_moveSpeed;

	//ワールド行列確定
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = m_rotBulletMat * transMat;
}

void Bullet::DrawLit()
{
	if (!m_spModel)return;

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_spModel, m_mWorld);
}

void Bullet::Init()
{
	if (!m_spModel)
	{
		m_spModel = std::make_shared<KdModelWork>();
		m_spModel->SetModelData("Asset/Models/Bullet/Arrow.gltf");
	}
	m_mWorld = Math::Matrix::CreateScale(10.0f);
}

void Bullet::shot(Math::Vector3 _pos, Math::Vector3 _dir)
{
	m_pos = _pos;

	m_moveDir = _dir;
	m_moveDir.Normalize();

	//照準へのベクトルと弾の進行ベクトルから弾の向き（回転行列）を作成

	//①ベクトルA・・・弾の現在の進行ベクトル
	Math::Vector3 vecA = m_mWorld.Backward();
	vecA.Normalize();

	//②ベクトルB・・・照準への進行ベクトル
	Math::Vector3 vecB = m_moveDir;
	vecB.Normalize();

	//①と②のベクトルの内積値から角度を算出
	float dot = vecA.Dot(vecB);
	float angle = acos(dot);

	//①と②のベクトル外積を利用して、回転するためのベクトル（回転軸）を作成
	Math::Vector3 rotAxis = vecA.Cross(vecB);

	//内積で算出した角度分、外積で算出したベクトル（回転軸）で回転する行列を作成
	//　= 弾がレティクルの方向を向く
	m_rotBulletMat = Math::Matrix::CreateFromAxisAngle(rotAxis,angle);
}
