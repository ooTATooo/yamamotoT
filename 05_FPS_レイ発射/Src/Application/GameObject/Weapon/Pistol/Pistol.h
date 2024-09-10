#pragma once

#include "../WeaponBase.h"

class Pistol :public WeaponBase
{
public:

	Pistol() { Init(); }
	~Pistol()override {};

	void Update()override;
	void Init()override;

	void ShotBullet(const bool rayFlg = false)override;

private:
};