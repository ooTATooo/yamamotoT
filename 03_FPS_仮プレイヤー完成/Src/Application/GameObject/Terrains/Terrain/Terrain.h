#pragma once

class Terrain : public KdGameObject
{
public:
	Terrain() { Init(); }
	virtual ~Terrain()override {}

	void Update()override;
	void DrawLit()override;

private:

	void Init()override;
	std::shared_ptr<KdModelWork> m_spModel = nullptr;

};