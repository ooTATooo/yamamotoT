#include "AnimationCamera.h"

#include "../../../Scene/GameScene/GameScene.h"

void AnimationCamera::Update()
{
	// 二点間の補完処理を行う
	std::shared_ptr<KdGameObject> spStart = m_wpStart.lock();
	std::shared_ptr<KdGameObject> spEnd = m_wpEnd.lock();
	
	// 対象が消えていたらアニメーション強制終了
	if (!spStart || !spEnd)
	{
		// 補完する為の存在なので破棄
		m_isExpired = true;
		return;
	}

	// 補完する行列の取得
	Math::Matrix startMat = spStart->GetCameraMatrix();
	Math::Matrix endMat = spEnd->GetCameraMatrix();

	// 回転の補完
	// クォータニオン用意
	Math::Quaternion startQue;
	Math::Quaternion endQue;
	Math::Quaternion nowQue;

	// 最初から行列からクォータニオン作成
	startQue = Math::Quaternion::CreateFromRotationMatrix(startMat);
	endQue = Math::Quaternion::CreateFromRotationMatrix(endMat);

	// 進行具合を加味した回転を求める
	// 球面線形補完
	nowQue = Math::Quaternion::Slerp(startQue, endQue, m_progress);

	m_mWorld = Math::Matrix::CreateFromQuaternion(nowQue);

	// 座標の補完
	// 線形補完
	Math::Vector3 startVec;
	Math::Vector3 endVec;

	startVec = startMat.Translation();
	endVec = endMat.Translation();

	// 進行具合を加味した座標を求める
	Math::Vector3 nowVec;

	// 線形補完
	nowVec = Math::Vector3::Lerp(startVec, endVec, m_progress);

	// ワールド行列を更新
	m_mWorld.Translation(nowVec);

	m_progress += m_speed;

	if (m_progress > 1.0f)
	{
		m_progress = 1.0f;

		m_isExpired = true;
	
		// カメラを追尾対象を終点オブジェクトに設定
		if (m_pNowScene)
		{
			m_pNowScene->SetCameraTarget(spEnd);
		}
	}
}

void AnimationCamera::Init()
{
	// オブジェクト名
	m_objName = "AnimationCamera";
}

void AnimationCamera::SetAnimationInfo(GameScene* scene, const std::shared_ptr<KdGameObject>& start, const std::shared_ptr<KdGameObject>& end, float spd)
{
	//現在のシーン
	m_pNowScene = scene;

	// 始点と終点を記憶
	m_wpStart = start;
	m_wpEnd = end;

	// 進行度とスピードを初期化
	m_progress = 0.0f;
	m_speed = spd;
}
