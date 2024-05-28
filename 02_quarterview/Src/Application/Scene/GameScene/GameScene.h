#pragma once

#include"../BaseScene/BaseScene.h"

class Player;

class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init() override;

	// プレイヤーの情報
	std::weak_ptr<Player> m_player;

	// スマートポインタの種類は3つ

	// shared_ptr	参照カウンタが増減する、アクセス可能

	// weak_ptr		参照カウンタが増減しない
	//				アドレスは保持できるがアクセスする権利は無い

	// unique_ptr	1つのポインタでしか所有できない
};
