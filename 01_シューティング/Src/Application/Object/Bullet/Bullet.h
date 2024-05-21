#pragma once
#include"../BaseObject.h"

class GameScene;

class Bullet :public BaseObject
{
public:

	Bullet() {}
	~Bullet() { Release(); }

	void Update()override;
	void Draw()override;
	void Init()override;

	void Shot(Math::Vector3 _shotPos);

	void SetOwner(GameScene* _owner) { m_owner = _owner; };

	void OnHit()override;
private:

	GameScene* m_owner = nullptr;

	void Release()override;

	Math::Vector3 m_movePow;

};