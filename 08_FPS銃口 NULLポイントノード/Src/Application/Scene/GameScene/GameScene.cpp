#include "GameScene.h"
#include"../SceneManager.h"
#include"../../main.h"

#include"Application/GameObject/Camera/FPSCamera/FPSCamera.h"
#include"Application/GameObject/Character/Player/Player.h"
#include"Application//GameObject/Terrains/Terrain/Terrain.h"
#include"Application/GameObject/Terrains/WoodenBox/WoodenBox.h"
#include"../../GameObject/Weapon/Pistol/Pistol.h"
#include"../../GameObject/UI/Reticle/Reticle.h"

void GameScene::Event()
{
	//Application::Instance().m_log.AddLog("test:%\n",test);
}

void GameScene::Init()
{
	//カーソルを非表示
	ShowCursor(false);

	//地形 地面
	std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	_terrain->Init();
	m_objList.push_back(_terrain);
	for (int i = 0; i < 5; i++)
	{
		std::shared_ptr<WoodenBox> _wood = std::make_shared<WoodenBox>();
		_wood->Init();
		_wood->SetPos({ -60.0f + i * 30,0,50.0f });
		m_objList.push_back(_wood);
	}

	//プレイヤー
	std::shared_ptr<Player> _player = std::make_shared<Player>();
	_player->Init();
	m_objList.push_back(_player);

	std::shared_ptr<Pistol> _pistol = std::make_shared<Pistol>();
	_pistol->Init();
	m_objList.push_back(_pistol);

	std::shared_ptr<Reticle> _reticle = std::make_shared<Reticle>();
	_reticle->Init();
	m_objList.push_back(_reticle);

	// カメラ初期化
	std::shared_ptr<FPSCamera> _camera = std::make_shared< FPSCamera>();
	_camera->Init();
	m_objList.push_back(_camera);

	//各オブジェクトに必要なデータを渡しておく
	_camera->SetTarget(_player);
	_pistol->SetParent(_player);
	_player->SetWeapon(_pistol);
	//_player->SetCamera(_camera);

}
