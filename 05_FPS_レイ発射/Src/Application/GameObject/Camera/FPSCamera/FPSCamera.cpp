#include "FPSCamera.h"

#include "../../Characters/Player/Player.h"

void FPSCamera::Init()
{
	// 親クラスの初期化呼び出し
	CameraBase::Init();
}

void FPSCamera::Update()
{
	// ターゲットの行列(有効な場合利用する)
	Math::Matrix _targetMat = Math::Matrix::Identity;
	const std::shared_ptr<const KdGameObject> _spTarget = m_wpTarget.lock();
	if (_spTarget)
	{
		_targetMat = _spTarget->GetMatrix();
	}

	m_mWorld = _targetMat;

	CameraBase::Update();
}
