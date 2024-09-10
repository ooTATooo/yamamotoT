#include "Player.h"
#include "Application/GameObject/Camera/CameraBase.h"
#include "Application/Scene/SceneManager.h"
#include "Application/GameObject/Weapon/WeaponBase .h"


void Player::Update()
{
	m_moveDir = Math::Vector3::Zero;

	if (GetAsyncKeyState('D') & 0x8000) { m_moveDir.x +=  1.0f; }
	if (GetAsyncKeyState('A') & 0x8000) { m_moveDir.x += -1.0f; }
	if (GetAsyncKeyState('W') & 0x8000) { m_moveDir.z +=  1.0f; }
	if (GetAsyncKeyState('S') & 0x8000) { m_moveDir.z += -1.0f; }
	if (GetAsyncKeyState(VK_SPACE) & 0x8000) 
	{
		if (!m_jumpKeyFlg)
		{
			m_gravity= -m_jumpPow;
			m_jumpKeyFlg = true;
		}
	}
	else
	{
		m_jumpKeyFlg = false;
	}

	//キャラ制御　銃発射レイver
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_leftKeyFlg)
		{
			m_leftKeyFlg = true;

			std::shared_ptr<WeaponBase> _spWeapon = m_wpWeapon.lock();
			if (_spWeapon)
			{
				_spWeapon->ShotBullet(true);
			}
		}
	}
	else
	{
		m_leftKeyFlg = false;
	}



	// カメラの回転
	UpdateRotateByMouse();

	//ベクトルの向きをY軸の回転行列で変換
	m_moveDir = m_moveDir.TransformNormal(m_moveDir, GetRotationMatrix());
	
	//確定した向き情報を正規化
	m_moveDir.Normalize();

	//座標更新
	m_pos += m_moveDir*m_moveSpeed;

	//重力をキャラに反映
	m_pos.y -= m_gravity;
	m_gravity += m_gravityPow;

	// キャラクターのワールド行列を創る処理
	Math::Matrix _trans = Math::Matrix::CreateTranslation(m_pos);

	Math::Matrix _rotation = GetRotationMatrix();

	m_mWorld = _rotation * _trans;
}

void Player::PostUpdate()
{
	//地形各種とレイ判定
	//レイ判定用に必要パラメーターを設定する構造体を宣言
	KdCollider::RayInfo rayInfo;
	//レイの発射位置（座標）を設定
	rayInfo.m_pos = m_pos;
	//段差の許容範囲を設定
	static const float enableStepHigh = .5f;//0.2までの高さならレイで上る
	rayInfo.m_pos.y = m_pos.y- m_adjusHeight + enableStepHigh;
	//レイの方向を設定
	rayInfo.m_dir = Math::Vector3::Down;
	//レイの長さを設定
	rayInfo.m_range = m_gravity + enableStepHigh ;
	//当たり判定をしたいタイプを設定
	rayInfo.m_type = KdCollider::TypeGround;
	//デバック用の譲歩としてライン描画を追加
	m_pDebugWire->AddDebugLine(rayInfo.m_pos, rayInfo.m_dir, rayInfo.m_range);//網の発射位置、線の方向、線の長さ
	std::list<KdCollider::CollisionResult> retRayList;
	//作成したレイ情報でオブジェクトリストに判定する
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(rayInfo, &retRayList);
	}
	//レイにあったリストから一番一回オブジェクトリストを検出
	bool hit = false;
	float maxOverLap = 0;
	Math::Vector3 groundPos = {};
	for (auto& ret : retRayList)
	{
		//レイが当たった場合の貫通した長さが一番長いもの探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			//着弾が速い場合
			maxOverLap = ret.m_overlapDistance;
			groundPos = ret.m_hitPos;
			groundPos.y += m_adjusHeight;
			hit = true;
		}
	}

	//当たっていたら
	if (hit)
	{
		m_pos = groundPos;
		m_gravity = 0.000f;
	}

}

void Player::Init()
{
	m_pos.y +=m_adjusHeight ;
	// ↓画面中央座標
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;
	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	//真ん中に固定するやつ

}

void Player::UpdateRotateByMouse()
{
	// マウスでカメラを回転させる処理
	POINT _nowPos;
	GetCursorPos(&_nowPos);

	POINT _mouseMove{};
	_mouseMove.x = _nowPos.x - m_FixMousePos.x;
	_mouseMove.y = _nowPos.y - m_FixMousePos.y;

	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	// 実際にカメラを回転させる処理(0.15はただの補正値)
	m_DegAng.x += _mouseMove.y * 0.15f;
	m_DegAng.y += _mouseMove.x * 0.15f;

	// 回転制御
	m_DegAng.x = std::clamp(m_DegAng.x, -80.f, 80.f);

}