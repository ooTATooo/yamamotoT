#pragma once

class Bullet:public KdGameObject
{
public:
	Bullet() {}
	~Bullet()override {}

	void Update()override;
	void DrawLit()override;
	void Init()override;

	void shot(Math::Vector3 _pos, Math::Vector3 _dir);

private:
	//モデル情報
	std::shared_ptr<KdModelWork>m_spModel = nullptr;

	//ワールド座標
	Math::Vector3 m_pos{};
	Math::Vector3 m_moveDir{};
	float m_moveSpeed=0.1f;
	//照準への回転行列
	Math::Matrix m_rotBulletMat;
};
