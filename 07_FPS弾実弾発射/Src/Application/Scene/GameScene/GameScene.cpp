#include "GameScene.h"
#include"../SceneManager.h"
#include"../../main.h"

#include"Application/GameObject/Camera/FPSCamera/FPSCamera.h"
#include"Application/GameObject/Character/Player/Player.h"
#include"Application//GameObject/Terrains/Terrain/Terrain.h"
#include"Application//GameObject/Terrains/WoodenBox/WoodenBox.h"
#include"Application/GameObject/Weapon/Pistol/Pistol.h"
#include"Application/GameObject/UI/UI.h"

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

	//BOX
	for (int i = 0; i < 5; i++)
	{
		std::shared_ptr<WoodenBox> _woodenBox = std::make_shared<WoodenBox>();
		_woodenBox->Init();
		_woodenBox->SetPos({ -60 + ((float)i * 30), 0, -50 });
		m_objList.push_back(_woodenBox);
	}
	//プレイヤー
	std::shared_ptr<Player> _player = std::make_shared<Player>();
	_player->Init();
	m_objList.push_back(_player);

	// カメラ初期化
	std::shared_ptr<FPSCamera> _camera = std::make_shared< FPSCamera>();
	_camera->Init();
	m_objList.push_back(_camera);

	//各オブジェクトに必要なデータを渡しておく
	_camera->SetTarget(_player);
	//_player->SetCamera(_camera);


	std::shared_ptr<Pistol> _Pistol = std::make_shared< Pistol>();
	_Pistol->Init();
	_Pistol->SetParent(_player);
	m_objList.push_back(_Pistol);
	_player->SetWeapon(_Pistol);

	std::shared_ptr<UI> _ui = std::make_shared<UI>();
	_ui->Init();
	m_objList.push_back(_ui);


}
