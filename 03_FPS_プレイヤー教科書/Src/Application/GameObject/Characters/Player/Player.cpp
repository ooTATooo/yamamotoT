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

	// キャラ制御(回転角度の情報を更新)
	UpdateRotateByMouse();

	// ベクトルの向きをY軸の回転行列で変換
	//const std::shared_ptr<const CameraBase> _spCamera = m_wpCamera.lock();
	//if (_spCamera)
	//{
	//	m_moveDir = m_moveDir.TransformNormal(m_moveDir, _spCamera->GetRotationYMatrix());
	//}

	//ベクトルの向きをY軸の回転行列で変換
	m_moveDir = m_moveDir.TransformNormal(m_moveDir, GetRotationYMatrix());

	// 確定した向き情報を正規化
	m_moveDir.Normalize();

	// 座標更新
	// 座標 += 向き情報(1.0f) * 移動速度
	m_pos += m_moveDir * m_moveSpeed;

	// ワールド行列確定
	Math::Matrix _rotMat = GetRotationMatrix();

	Math::Matrix _transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = _rotMat * _transMat;
}

void Player::UpdateRotateByMouse()
{
	// マウスでカメラを回転させる処理
	POINT _nowPos;
	GetCursorPos(&_nowPos);

	POINT _mouseMove{};
	_mouseMove.x = _nowPos.x - m_fixMousePos.x;
	_mouseMove.y = _nowPos.y - m_fixMousePos.y;

	SetCursorPos(m_fixMousePos.x, m_fixMousePos.y);

	// 実際にカメラを回転させる処理(0.15はただの補正値)
	m_degAng.x += _mouseMove.y * 0.15f;
	m_degAng.y += _mouseMove.x * 0.15f;

	// 回転制御
	m_degAng.x = std::clamp(m_degAng.x, -70.0f, 70.0f);
}

void Player::Init()
{
	// 地面から補正値分上げる
	m_pos.y = m_adjustHeight;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}
