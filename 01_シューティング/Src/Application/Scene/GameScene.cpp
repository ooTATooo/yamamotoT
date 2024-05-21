#include "GameScene.h"

#include"../Object/Player/Player.h"
#include"../Object/Enemy/Enemy.h"
#include"../Object/Bullet/Bullet.h"

void GameScene::PreUpdate()
{
	// Updateの前の更新処理
	// オブジェクトリストの整理をしておく

	// イテレータ ・・・ コンテナクラス用のポインタ(のようなもの)
	// コンテナを先頭から末尾まで

	// イテレータ作成
	//std::vector<std::shared_ptr<BaseObject>>::iterator it;
	//it = m_objList.begin();

	// イテレータ作成 auto版
	auto it = m_objList.begin();

	while (it != m_objList.end())	// end()は最後の要素の1個後ろを返す
	{
		if (!(*it)->GetAliveFlg())
		{
			// 無効なオブジェクトをリストから削除
			it = m_objList.erase(it);
		}
		else
		{
			it++;	// 次の要素へイテレータを進める
		}
	}

	// ↑の後には有効なオブジェクトだけのリストになっている
}

void GameScene::Update()
{
	//m_player->Update();
	//m_enemy->Update();

	if (rand() % 100 + 1 < 3)
	{
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
		enemy->Init();
		enemy->SetPos(640.0f, 0.0f);
		enemy->SetMovePow({ -2.0f, -2.0, 0.0f });
		m_objList.push_back(enemy);
	}

	// 全オブジェクトの更新関数を呼ぶ
	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList[i]->Update();
	}

}

void GameScene::Draw()
{
	//m_player->Draw();
	//m_enemy->Draw();

	// 全オブジェクトの描画関数を呼ぶ
	// 範囲ベースFor
	//for (auto& obj: m_objList)
	//{
	//	obj->Draw();
	//}

	for (int i = 0; i < m_objList.size(); i++)
	{
		m_objList[i]->Draw();
	}
}

void GameScene::Init()
{
	// プレイヤー
	//m_player = new Player();						//生ポ
	//m_player = std::make_shared<Player>();		//スマポ
	//m_player->Init();
	//m_player->SetOwner(this);
	std::shared_ptr<Player> player = std::make_shared<Player>();
	player->Init();
	player->SetOwner(this);
	m_objList.push_back(player);

	// エネミー
	//m_enemy = std::make_shared<Enemy>();
	//m_enemy->Init();
	for (float i = 0; i < 10; i++)
	{
		std::shared_ptr<Enemy> enemy = std::make_shared<Enemy>();
		enemy->Init();
		enemy->SetPos((128.0f * i) - 640.0f, 360.0f);
		m_objList.push_back(enemy);
	}
}

void GameScene::Release()
{
	//delete m_player;		//生ポ（shared_ptrは自動削除）
}
