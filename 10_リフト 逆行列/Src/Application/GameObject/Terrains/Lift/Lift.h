#pragma once

class Lift :public KdGameObject
{
public:

	Lift() {}
	~Lift()override {}

	void Update()override;
	void Init()override;
	void DrawLit()override;

	bool IsRideable()const override { return true; }


private:

	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	Math::Vector3 m_pos = Math::Vector3::Zero;

	float m_degAng = 0;

	const float m_moveVal = 30.0f;
};