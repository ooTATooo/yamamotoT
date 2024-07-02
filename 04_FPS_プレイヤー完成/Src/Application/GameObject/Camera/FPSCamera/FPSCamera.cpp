#include "FPSCamera.h"

#include "../../Characters/Player/Player.h"

void FPSCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();

	// 基準点(ターゲット)の目線
	m_mLocalPos = Math::Matrix::CreateTranslation(0, 1.5f, 0.0f);
}

void FPSCamera::Update()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix _targetMat = Math::Matrix::Identity;
	Math::Matrix _rotMat = Math::Matrix::Identity;
	const std::shared_ptr<const Player> _spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = Math::Matrix::CreateTranslation(_spTarget->GetPos());
		_rotMat = _spTarget->GetRotationMatrix();
	}

	m_mWorld = m_mLocalPos * _rotMat * _targetMat;

	CameraBase::Update();
}
