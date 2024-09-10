#include "GameScene.h"
#include "../SceneManager.h"

#include "../../main.h"
#include "../../GameObject/Camera/FPSCamera/FPSCamera.h"
#include "../../GameObject/Terrains/Terrain/Terrain.h"
#include "../../GameObject/Characters/Player/Player.h"
#include "../../GameObject/Weapon/Pistol/Pistol.h"
#include "../../GameObject/UI/Reticle/Reticle.h"

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

	std::shared_ptr<Pistol> _pistol = std::make_shared<Pistol>();
	AddObject(_pistol);

	std::shared_ptr<FPSCamera> _camera = std::make_shared<FPSCamera>();
	AddObject(_camera);

	std::shared_ptr<Reticle> _reticle = std::make_shared<Reticle>();
	AddObject(_reticle);

	// 各オブジェクトに必要なデータを渡しておく
	_pistol->SetParent(_player);
	_camera->SetTarget(_player);
}
