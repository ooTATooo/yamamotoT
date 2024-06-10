#include "Enemy.h"

#include "../../Scene/SceneManager.h"

void Enemy::Update()
{
	int run[4] = { 3,4,3,5 };

	m_poly->SetUVRect(run[(int)m_animeCnt]);

	m_animeCnt += m_animeSpeed;
	if (m_animeCnt >= 4)
	{
		m_animeCnt = 0;
	}

	m_pos.y -= m_gravity;
	m_gravity += 0.005f;

	m_moveVec = Math::Vector3::Zero;

	// 対象座標ー自分の座標
	Math::Vector3 dis;

	const std::shared_ptr<KdGameObject> player = m_target.lock();

	if (player)
	{
		dis = player->GetPos() - m_pos;

		if (dis.Length() < m_searchArea)
		{
			m_chaseFlg = true;
		}
		else
		{
			m_chaseFlg = false;
		}
	}

	if (m_chaseFlg)
	{
		m_moveVec = dis;
	}

	m_moveVec.Normalize();
	m_pos += m_moveVec *= m_speed;

}

void Enemy::PostUpdate()
{
	// 球判定用の変数を作成
	KdCollider::SphereInfo sphere;
	// 球の中心点を設定
	sphere.m_sphere.Center = m_pos;
	sphere.m_sphere.Center.y += 0.5f;
	// 球の半径を設定
	sphere.m_sphere.Radius = m_searchArea;
	// 当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeBump;

	// デバッグ表示
	Math::Color color = { 0,1,0,1 };
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, color);


	// レイ判定用に必要パラメータを設定する構造体を宣言
	KdCollider::RayInfo rayinfo;

	// レイの発射位置(座標)を設定
	rayinfo.m_pos = m_pos;

	// 少し高いところから飛ばす
	//rayinfo.m_pos.y += 0.1f;

	// 段差の許容範囲を設定
	static const float enableStepHigh = 0.2f;
	rayinfo.m_pos.y += enableStepHigh;

	// レイの方向を設定
	rayinfo.m_dir = { 0.0f,-1.0f,0.0f };

	// レイの長さを確定
	rayinfo.m_range = m_gravity + enableStepHigh;

	// 当たり判定をしたいタイプを設定
	rayinfo.m_type = KdCollider::TypeGround;

	// デバッグ用の情報としてライン描画を追加
	m_pDebugWire->AddDebugLine(rayinfo.m_pos, rayinfo.m_dir, rayinfo.m_range);

	// レイに当たったオブジェクト情報を格納するリスト
	std::list<KdCollider::CollisionResult> retRayList;

	// 作成したレイ情報でオブジェクトと当たり判定をする
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(rayinfo, &retRayList);
	}

	// レイに当たったリストから一番近いオブジェクトを検出
	bool hit = false;
	float maxOverLap = 0;
	Math::Vector3 groundPos = {};

	for (auto& ret : retRayList)
	{
		// レイが当たった場合の貫した長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			groundPos = ret.m_hitPos;
			hit = true;
		}
	}

	if (hit)
	{
		m_pos = groundPos;
		m_gravity = 0;
	}

	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void Enemy::Init()
{
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/Enemy.png");
	m_poly->SetSplit(6, 6);
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_pos = Math::Vector3::Zero;
	m_dir = Math::Vector3::Zero;
	m_animeCnt = 0;
	m_animeSpeed = 0.1f;
	m_speed = 0.05f;
	m_gravity = 0;
	m_mWorld = Math::Matrix::Identity;
	m_searchArea = 3.0f;
	m_chaseFlg = false;
	// デバッグワイヤー生成
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Enemy::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}

void Enemy::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}

void Enemy::SetTarget(const std::weak_ptr<KdGameObject> _target)
{
	if(!_target.expired())
	{
		m_target = _target;
	}
}
