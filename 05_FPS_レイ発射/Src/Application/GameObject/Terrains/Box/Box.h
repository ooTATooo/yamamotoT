#pragma once

class Box : public KdGameObject
{
public:
	Box() { Init(); }
	virtual ~Box()override {}

	void DrawLit()override;

private:

	void Init()override;
	std::shared_ptr<KdModelWork> m_spModel = nullptr;

};