#pragma once

class Attack :public KdGameObject
{
public:

	Attack() { Init(); }
	~Attack()override {}

	void Update()override;
	void PreUpdate()override;
	void Init()override;
	void DrawUnLit()override;

	void OnHit()override;

private:

	std::shared_ptr<KdSquarePolygon> m_poly;

	Math::Vector3 m_pos;

	Math::Vector3 m_dir;

	float m_animeCnt = 0;

	float m_animeSpeed;

	float m_attackArea = 0.3f;

	float m_gravity;

};