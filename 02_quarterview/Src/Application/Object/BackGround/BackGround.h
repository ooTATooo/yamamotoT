#pragma once

class BackGround :public KdGameObject
{
public:

	BackGround() {}
	~BackGround()override {}

	void DrawUnLit()override;
	void Init()override;

private:

	KdSquarePolygon m_polygon;
};