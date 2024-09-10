#pragma once
class Reticle:public KdGameObject
{
public:
	Reticle() {};
	~Reticle()override {};

	void Init()override;
	void DrawSprite()override;

private:
	KdTexture m_tex;
	Math::Vector2 m_pos;
	Math::Vector2 m_texSize;
	Math::Vector2 m_scale;
	Math::Rectangle m_rect;
	Math::Color m_color;
};
