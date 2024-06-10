#pragma once

class Enemy :public KdGameObject
{
public:

	Enemy() {}
	~Enemy() override {};

	void Update()override;
	void PostUpdate()override;
	void Init()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

	void SetPos(Math::Vector3 _pos) { m_pos = _pos; }
	void SetTarget(const std::weak_ptr<KdGameObject> _target);

private:

	std::shared_ptr<KdSquarePolygon> m_poly = nullptr;

	std::weak_ptr<KdGameObject> m_target;

	Math::Vector3 m_pos = Math::Vector3::Zero;
	Math::Vector3 m_dir = Math::Vector3::Zero;
	Math::Vector3 m_moveVec = Math::Vector3::Zero;
	float m_animeCnt = 0;
	float m_animeSpeed = 0;
	float m_speed = 0;
	float m_gravity = 0;

	float m_searchArea = 0;
	bool m_chaseFlg = false;
};