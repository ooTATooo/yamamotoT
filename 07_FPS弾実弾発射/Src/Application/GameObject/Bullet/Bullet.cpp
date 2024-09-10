#include "Bullet.h"

void Bullet::Update()
{
	//座標更新
	m_pos += m_moveDir * m_moveSpeed;
	
	//ワールド行列確定
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix _scale= Math::Matrix::CreateScale(10.0f);

	m_mWorld = _scale* m_rotBulletMat*_transMat;
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

void Bullet::Shot(Math::Vector3 _pos, Math::Vector3 _dir)
{
	m_pos = _pos;
	m_moveDir = _dir;
	m_moveDir.Normalize();

	//照準へのベクトルと弾の進行ベクトル弾の向き（回転行列）を作成

	//①ベクトルA・・・弾の現在の進行ベクトル
	Math::Vector3 _vecA = m_mWorld.Backward();
	_vecA.Normalize();

	//②ベクトルB・・・照準への進行ベクトル
	Math::Vector3 _vecB = m_moveDir;
	_vecB.Normalize();

	//①と②のベクトルの内関値から角度を算出
	float _dot = _vecA.Dot(_vecB);	//内関値を算出	//Dot関掛け算
	float _angle = acos(_dot);		//内関値２つのベクトルの角度を算出

	//①と②のベクトルの外積を利用して、回転するためのベクトル（回転軸）を作成
	Math::Vector3 _rotAxis = _vecA.Cross(_vecB);

	//内関で算出した角度分、外積で算出したベクトル（回転軸)回転する行列を作成
	//＝弾がレティクルの方向を向く
	
	m_rotBulletMat =Math::Matrix::CreateFromAxisAngle(_rotAxis,_angle);
}
