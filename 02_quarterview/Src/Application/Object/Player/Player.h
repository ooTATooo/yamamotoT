#pragma once

class Player :public KdGameObject
{
public:

	enum DirType
	{
		Up = 1 << 0,
		Down = 1 << 1,
		Left = 1 << 2,
		Right = 1 << 3,
	};

	// アニメーション情報
	struct AnimationInfo
	{
		int start;
		int end;
		float count;
		float speed;
	};

	Player() {}
	~Player()override {}

	void Update()override;
	void PostUpdate()override;
	void Init()override;
	void GenerateDepthMapFromLight()override;
	void DrawLit()override;

private:

	std::shared_ptr<KdSquarePolygon> m_poly;

	// アニメーション情報
	AnimationInfo m_animeInfo;

	// キャラが向いている方向種類　ビット管理
	UINT m_dirType;

	Math::Vector3 m_pos;

	Math::Vector3 m_dir;

	float m_spped;

	float m_gravity;
};