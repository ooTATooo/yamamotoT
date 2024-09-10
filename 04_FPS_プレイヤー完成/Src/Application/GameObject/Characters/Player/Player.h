#pragma once

class Player :public KdGameObject
{
public:

	Player() { Init(); }
	~Player()override {}

	void Update()override;

private:

	void Init()override;

	void UpdateRotateByMouse();

	const Math::Matrix GetRotationYMatrix() const
	{
		return Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_degAng.y));
	}

	const Math::Matrix GetRotationMatrix()const
	{
		return Math::Matrix::CreateFromYawPitchRoll(
			DirectX::XMConvertToRadians(m_degAng.y),
			DirectX::XMConvertToRadians(m_degAng.x),
			DirectX::XMConvertToRadians(m_degAng.z));
	}

	// ワールド座標
	Math::Vector3 m_pos = Math::Vector3::Zero;

	// 回転角度
	Math::Vector3 m_degAng = Math::Vector3::Zero;

	// 進行方向(ベクトルの向き)
	Math::Vector3 m_moveDir = Math::Vector3::Zero;

	// 移動速度(ベクトルの大きさ)
	const float m_moveSpeed = 0.6f;

	// プレイヤー
	const float m_adjustHeight = 10.0f;

	// 回転用マウス座標の差分
	POINT m_FixMousePos{ 640,360 };
};