#include "GameScene.h"
#include"../SceneManager.h"

#include "../../GameObject/Camera/TrackingCamera/TrackingCamera.h"
#include "../../GameObject/Character/Robot/Robot.h"
#include "../../GameObject/Terrains/Ground/Ground.h"
#include "../../GameObject/Terrains/Torii/Torii.h"
#include "../../GameObject/Terrains/Lift/Lift.h"
#include "../../GameObject/Camera/AnimationCamera/AnimationCamera.h"

bool GameScene::SetCameraTarget(std::weak_ptr<KdGameObject> target)
{
	std::shared_ptr<KdGameObject> spTarget = target.lock();

	// 対象が有効ならカメラのターゲットに設定
	if (spTarget)
	{
		std::shared_ptr<CameraBase> camera = m_wpCamera.lock();
		if (camera)
		{
			camera->SetTarget(spTarget);
		}

		// ターゲットの名前を更新
		m_strCameraTarget = spTarget->GetObjName();

		return true;
	}

	return false;
}

void GameScene::ChangeCameraTarget()
{
	// アニメーション中は切り替えない
	std::shared_ptr<KdGameObject> animCam = FindObjectWithName("AnimationCamera");
	if (animCam)return;

	std::shared_ptr<KdGameObject> now = FindObjectWithName(m_strCameraTarget);

	// 新しいターゲットの名前を設定	※非推奨
	if (m_strCameraTarget == "Robot")
	{
		m_strCameraTarget = "Torii";
	}
	else if (m_strCameraTarget == "Torii")
	{
		m_strCameraTarget = "Lift";
	}
	else if (m_strCameraTarget == "Lift")
	{
		m_strCameraTarget = "Robot";
	}

	// 新しいターゲットを検索
	std::shared_ptr<KdGameObject> target = FindObjectWithName(m_strCameraTarget);
	if (!target)return;

	// 補完用のオブジェクトを作成
	std::shared_ptr<AnimationCamera> spNewAnimCam = std::make_shared<AnimationCamera>();
	spNewAnimCam->Init();
	spNewAnimCam->SetAnimationInfo(this, now, target);
	spNewAnimCam->Update();	// 苦肉の策
	AddObject(spNewAnimCam);

	// 補完用のオブジェクトをカメラのターゲットに切り替える
	std::shared_ptr<CameraBase> spCamera = m_wpCamera.lock();
	if (spCamera)
	{
		spCamera->SetTarget(spNewAnimCam);
	}
}

std::shared_ptr<KdGameObject> GameScene::FindObjectWithName(const std::string& name)
{
	for (auto& obj : m_objList)
	{
		if (obj->GetObjName() == name)
		{
			return obj;
		}
	}

	// 見つからなければ null を返す
	return nullptr;
}

void GameScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		ChangeCameraTarget();
	}
}

void GameScene::Init()
{
	// カーソルを非表示
	ShowCursor(false);

	// 地形 地面
	std::shared_ptr<Ground> _ground = std::make_shared<Ground>();
	_ground->Init();
	m_objList.push_back(_ground);

	// 地形 地面
	std::shared_ptr<Torii> _torii = std::make_shared<Torii>();
	_torii->Init();
	m_objList.push_back(_torii);

	// リフト
	std::shared_ptr<Lift> _lift;
	_lift = std::make_shared<Lift>();
	_lift->Init();
	m_objList.push_back(_lift);

	// ロボット
	std::shared_ptr<Robot> _robot;
	_robot = std::make_shared<Robot>();
	_robot->Init();
	m_objList.push_back(_robot);

	// カメラ
	std::shared_ptr<TrackingCamera> _camera = std::make_shared<TrackingCamera>();
	_camera->Init();
	m_objList.push_back(_camera);

	// 必要なデータを渡しておく
	_camera->SetTarget(_robot);

	m_wpCamera = _camera;
}
