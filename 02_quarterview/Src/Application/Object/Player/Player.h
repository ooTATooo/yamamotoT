#pragma once

class Player :public KdGameObject
{
public:

	Player() {}
	~Player()override {}

	void Update()override;
	void PostUpdate()override;
	void Init()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

private:

	std::shared_ptr<KdSquarePolygon> m_poly;

	Math::Vector3 m_pos;

	Math::Vector3 m_dir;

	float m_spped;
};