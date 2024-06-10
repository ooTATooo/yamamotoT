#include "GameScene.h"
#include"../SceneManager.h"

#include "../../Object/BackGround/BackGround.h"
#include "../../Object/Ground/Ground.h"
#include "../../Object/Player/Player.h"
#include "../../Object/Enemy/Enemy.h"

void GameScene::Event()
{
	// プレイヤーの座標を取得する
	Math::Vector3 playerPos = {};

	// weak_ptrで所持している m_player が有効か調べる
	// expired()	期限切れならtrueを返す
	if (!m_player.expired())
	{
		playerPos = m_player.lock()->GetPos();
	}

	// カメラの回転行列を作成
	Math::Matrix rotMat;
	rotMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(30));

	// カメラの座標行列を作成
	Math::Matrix transMat;
	transMat = Math::Matrix::CreateTranslation(Math::Vector3{ 0, 3, -3 } + playerPos);

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

	std::shared_ptr<Player> player = std::make_shared <Player>();
	player->Init();
	AddObject(player);

	for (int i = 0; i < 20; i++)
	{
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
		enemy->Init();
		enemy->SetPos({ -50.0f + (10.0f * i),0,20 });
		enemy->SetTarget(player);
		AddObject(enemy);
	}


	// プレイヤーの情報を保持しておく
	m_player = player;
}
