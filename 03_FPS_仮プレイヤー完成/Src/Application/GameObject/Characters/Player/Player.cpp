#include "Player.h"

#include "../../Camera/CameraBase.h"

void Player::Update()
{
	// 進行方向クリア
	m_moveDir = Math::Vector3::Zero;

	// キャラ制御(進行ベクトルの情報更新)
	if (GetAsyncKeyState('W') & 0x8000) { m_moveDir += { 0, 0, 1 }; }
	if (GetAsyncKeyState('S') & 0x8000) { m_moveDir += { 0, 0, -1 }; }
	if (GetAsyncKeyState('A') & 0x8000) { m_moveDir += { -1, 0, 0 }; }
	if (GetAsyncKeyState('D') & 0x8000) { m_moveDir += { 1, 0, 0 }; }

	// ベクトルの向きをY軸の回転行列で変換
	const std::shared_ptr<const CameraBase> _spCamera = m_wpCamera.lock();
	if (_spCamera)
	{
		m_moveDir = m_moveDir.TransformNormal(m_moveDir, _spCamera->GetRotationYMatrix());
	}

	// 確定した向き情報を正規化
	m_moveDir.Normalize();

	// 座標更新
	// 座標 += 向き情報(1.0f) * 移動速度
	m_pos += m_moveDir * m_moveSpeed;

	// ワールド行列確定
	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = _transMat;
}

void Player::Init()
{
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}
