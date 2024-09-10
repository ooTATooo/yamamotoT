#pragma once

class Reticle : public KdGameObject
{
public:

	Reticle() { Init(); }
	~Reticle()override {}

	void DrawSprite()override;

	void Init()override;

private:

	KdTexture m_tex;
};