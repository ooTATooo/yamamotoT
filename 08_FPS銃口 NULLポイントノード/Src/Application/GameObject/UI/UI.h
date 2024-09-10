#pragma once

class UI:public KdGameObject
{
public:
	UI() {};
	~UI() {};

	void DrawSprite()override;
	void Init()override;
private:

	std::shared_ptr<KdTexture> m_tex=nullptr;
};

