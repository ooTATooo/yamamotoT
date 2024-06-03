#include "Player.h"

#include "../../Scene/SceneManager.h"

void Player::Update()
{
	m_dir = Math::Vector3::Zero;

	if (GetAsyncKeyState(VK_UP) & 0x8000) { m_dir += { 0, 0, 1 }; }
	if (GetAsyncKeyState(VK_DOWN) & 0x8000) { m_dir += { 0, 0, -1 }; }
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) { m_dir += { -1, 0, 0 }; }
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { m_dir += { 1, 0, 0 }; }

	m_dir.Normalize();

	m_pos += m_dir * m_spped;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) { m_gravity = -0.1f; }

	// 重力をキャラに反映
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;

	m_poly->SetUVRect(12);


	//======================================
	// 当たり判定		レイ判定	ここから
	//======================================

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

	//======================================
	// 当たり判定		レイ判定	ここまで
	//======================================
}

void Player::PostUpdate()
{
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = transMat;
}

void Player::Init()
{
	m_poly = std::make_shared<KdSquarePolygon>();
	m_poly->SetMaterial("Asset/Textures/Player.png");
	m_poly->SetSplit(4, 8);

	// 初期アニメーション情報
	m_animeInfo.start = 4;
	m_animeInfo.end = 7;
	m_animeInfo.count = 0;
	m_animeInfo.speed = 0.2f;

	// 向いている方向
	m_dirType = DirType::Down;

	m_poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_pos = m_mWorld.Translation();
	m_spped = 0.1f;
	m_gravity = 0.0f;
	m_mWorld = Math::Matrix::Identity;

	// デバッグワイヤー生成
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_poly, m_mWorld);
}
