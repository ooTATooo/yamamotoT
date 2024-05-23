#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Object/BackGround/BackGround.h"
#include "../../Object/Ground/Ground.h"

void GameScene::Event()
{
	// カメラの回転行列を作成
	Math::Matrix rotMat;
	rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(30));

	// カメラの座標行列を作成
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(0, 3, -3);

	// 行列合成
	Math::Matrix mat;
	mat = rotMat * transMat;

	// カメラに行列をセット
	// この時点では画面には反映されない
	m_camera->SetCameraMatrix(mat);
}

void GameScene::Init()
{
	// カメラ生成＆視野角設定
	m_camera = std::make_unique<KdCamera>();	//1 メモリ確保
	m_camera->SetProjectionMatrix(60);			//2	視野角設定

	// 背景
	std::shared_ptr<BackGround> back = std::make_shared<BackGround>();
	back->Init();
	AddObject(back);

	std::shared_ptr<Ground> ground = std::make_shared<Ground>();
	ground->Init();
	AddObject(ground);
}
