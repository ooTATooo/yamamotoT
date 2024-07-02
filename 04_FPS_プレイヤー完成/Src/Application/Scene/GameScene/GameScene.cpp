#include "GameScene.h"
#include "../SceneManager.h"

#include "../../main.h"
#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Terrains/Terrain/Terrain.h"
#include "../../GameObject/Characters/Player/Player.h"

void GameScene::Event()
{

}

void GameScene::Init()
{
	// カーソル非表示
	ShowCursor(false);

	std::shared_ptr<Terrain> _terrain = std::make_shared<Terrain>();
	AddObject(_terrain);

	std::shared_ptr<Player> _player = std::make_shared<Player>();
	AddObject(_player);

	std::shared_ptr<FPSCamera> _camera = std::make_shared<FPSCamera>();
	AddObject(_camera);

	// 各オブジェクトに必要なデータを渡しておく
	//_player->SetCamera(_camera);
	_camera->SetTarget(_player);
}
