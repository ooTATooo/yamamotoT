#include "Player.h"

#include "../../Scene/SceneManager.h"

void Player::Update()
{
	m_dir = Math::Vector3::Zero;
	UINT oldDirType = m_dirType;	// 前回の方向を退避
	m_dirType = 0;		// ビット列クリア

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_dir += { 0, 0, 1 };
		m_dirType |= DirType::Up;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_dir += { 0, 0, -1 };
		m_dirType |= DirType::Down;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_dir += { -1, 0, 0 };
		m_dirType |= DirType::Left;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_dir += { 1, 0, 0 };
		m_dirType |= DirType::Right;
	}


	// 向きが変わっていればアニメーション情報変更
	if (m_dirType != 0 && m_dirType != oldDirType)
	{
		ChangeAnimation();
	}
	// 変わってなければ元の向き(退避データ)に戻す
	else
	{
		m_dirType = oldDirType;
	}

	m_dir.Normalize();

	m_pos += m_dir * m_speed;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) { m_gravity = -0.1f; }

	// 重力をキャラに反映
	m_pos.y -= m_gravity;
	m_gravity += 0.005f;

	// アニメーション更新
	m_animeInfo.count += m_animeInfo.speed;
	int animeCnt = m_animeInfo.start + m_animeInfo.count;

	// 最後のコマまで表示し終えたらループさせる
	if (animeCnt > m_animeInfo.end)
	{
		animeCnt = m_animeInfo.start;
		m_animeInfo.count = 0;
	}

	m_poly->SetUVRect(animeCnt);


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
	m_speed = 0.1f;
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

void Player::ChangeAnimation()
{
	if (m_dirType & DirType::Up)
	{
		m_animeInfo.start = 24;
		m_animeInfo.end = 27;
	}
	if (m_dirType & DirType::Down)
	{
		m_animeInfo.start = 4;
		m_animeInfo.end = 7;
	}
	if (m_dirType & DirType::Left)
	{
		m_animeInfo.start = 12;
		m_animeInfo.end = 15;
	}
	if (m_dirType & DirType::Right)
	{
		m_animeInfo.start = 16;
		m_animeInfo.end = 19;
	}

	if (m_dirType == (DirType::Up | DirType::Left))
	{
		m_animeInfo.start = 20;
		m_animeInfo.end = 23;
	}
	if (m_dirType == (DirType::Up | DirType::Right))
	{
		m_animeInfo.start = 28;
		m_animeInfo.end = 31;
	}
	if (m_dirType == (DirType::Down | DirType::Left))
	{
		m_animeInfo.start = 0;
		m_animeInfo.end = 3;
	}
	if (m_dirType == (DirType::Down | DirType::Right))
	{
		m_animeInfo.start = 8;
		m_animeInfo.end = 11;
	}

	m_animeInfo.count = 0;
	m_animeInfo.speed = 0.2f;
}
