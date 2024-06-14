#include "Attack.h"

#include "../../Scene/SceneManager.h"

void Attack::Update()
{
	m_poly->SetUVRect((int)m_animeCnt);

	m_animeCnt += m_animeSpeed;
	if (m_animeCnt >= 9)
	{
		m_isExpired = true;
	}
}

void Attack::PreUpdate()
{
	// 球判定用の変数を作成
	KdCollider::SphereInfo sphere;
	// 球の中心点を設定
	sphere.m_sphere.Center = GetPos();
	sphere.m_sphere.Center.y += 0.5f;
	// 球の半径を設定
	sphere.m_sphere.Radius = m_attackArea;
	// 当たり判定をしたいタイプを設定
	sphere.m_type = KdCollider::TypeDamage;

	// デバッグ表示
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, kRedColor);

	std::list<KdCollider::CollisionResult> retSphereList;

	bool hit = false;
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		hit = obj->Intersects(sphere, &retSphereList);

		if (hit)
		{
			// Hit時の相手オブジェクトの処理
			obj->OnHit();

			// Hit時の自分の処理
			OnHit();

			break;
		}
	}
}

void Attack::Init()
{
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/Attack.png");
	m_poly->SetSplit(9, 1);
	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_animeSpeed = 1.0f;
	m_attackArea = 0.3f;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Attack::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}

void Attack::OnHit()
{
	m_isExpired = true;
}
