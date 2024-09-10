#include "Player.h"
#include "Application/GameObject/Camera/CameraBase.h"
#include"../../../Scene/SceneManager.h"
#include"../../../GameObject/Weapon/WeaponBase.h"

void Player::Init()
{
	m_pos.y += m_adjusHeight;
	// ↓画面中央座標
	m_FixMousePos.x = 640;
	m_FixMousePos.y = 360;
	SetCursorPos(m_FixMousePos.x, m_FixMousePos.y);

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
	//真ん中に固定するやつ

}

void Player::Update()
{
	m_moveDir = Math::Vector3::Zero;

	if (GetAsyncKeyState('D') & 0x8000) { m_moveDir.x +=  1.0f; }
	if (GetAsyncKeyState('A') & 0x8000) { m_moveDir.x += -1.0f; }
	if (GetAsyncKeyState('W') & 0x8000) { m_moveDir.z +=  1.0f; }
	if (GetAsyncKeyState('S') & 0x8000) { m_moveDir.z += -1.0f; }
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!m_key)
		{
			m_key = true;
			
			m_gravity = -m_jumoPow;
		}
	}
	else
	{
		m_key = false;
	}

	//キャラ制御　銃発射　レイVER
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_leftKeyFlg)
		{
			m_leftKeyFlg = true;
			std::shared_ptr<WeaponBase>spWeapon = m_wpWeapon.lock();
			if (spWeapon)
			{
				spWeapon->ShotBullet(true);
			}
		}
	}
	else
	{
		m_leftKeyFlg = false;
	}

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		if (!m_rightKeyFlg)
		{
			m_rightKeyFlg = true;
			std::shared_ptr<WeaponBase>spWeapon = m_wpWeapon.lock();
			if (spWeapon)
			{
				spWeapon->ShotBullet();
			}
		}
	}
	else
	{
		m_rightKeyFlg = false;
	}
	

	// カメラの回転
	UpdateRotateByMouse();

	//ベクトルの向きをY軸の回転行列で変換
	//m_moveDir = m_moveDir.TransformNormal(m_moveDir, GetRotationMatrix());
	m_moveDir = m_moveDir.TransformNormal(m_moveDir, GetRotationYMatrix());
	
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
	//レイ判定
	KdCollider::RayInfo ray;
	//飛ばす位置
	ray.m_pos = m_pos + Math::Vector3{ 0,-m_adjusHeight,0 };
	//長さ
	static const float enableStepHeight = 0.5f;
	ray.m_range = m_gravity+ enableStepHeight;
	//方向
	ray.m_dir = Math::Vector3::Down;
	//タイプ
	ray.m_type = KdCollider::TypeGround;
	//当たったOBJの情報を格納するリスト
	std::list<KdCollider::CollisionResult>retRayList;
	for (auto& obj : SceneManager::Instance().GetObjList())
	{
		obj->Intersects(ray, &retRayList);
	}

	bool hit = false;
	float maxOverLap = 0;
	Math::Vector3 hitPos = {};

	for (auto& ret : retRayList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			hit = true;
		}
	}

	if (hit)
	{
		m_pos = hitPos + Math::Vector3{0,m_adjusHeight,0};
		m_gravity = 0;
	}
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