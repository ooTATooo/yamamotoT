#pragma once 

class Player;

class Cloud :public KdGameObject
{
public:

	Cloud() {}
	~Cloud()override {}

	void Update()override;
	void Init()override;
	void DrawUnLit()override;

	void SetPlayer(const std::shared_ptr<Player>& _player) { m_wpPlayer = _player; }

private:

	std::shared_ptr<KdSquarePolygon> m_spPoly = nullptr;

	std::weak_ptr<Player> m_wpPlayer;

	Math::Vector3 m_pos = Math::Vector3::Zero;

	Math::Vector3 m_ang = Math::Vector3::Zero;
};