#pragma once

//基本敵にヘッダーファイルの中で
//別のヘッダーファイルをインクルードするのはNG
//継承元クラスのヘッダーのみインクルードが必要なので可とする
#include"../BaseObject.h"

class GameScene;

class Player :public BaseObject
{
public:
	Player() {}
	~Player() { Release(); }

	//基底クラスの仮想関数をオーバードライブ
	void Update()override;
	void Draw()override;
	void Init()override;

	void SetOwner(GameScene* _owner) { m_owner = _owner; };

private:

	GameScene* m_owner = nullptr;

	void Release()override;

	int m_shotInterval;

};