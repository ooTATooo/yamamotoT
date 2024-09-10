class CameraBase;
class WeaponBase;

class Player:public KdGameObject
{
public:
	Player() {};
	~Player() override {};

	void Update()override;
	void PostUpdate()override;

	void Init()override;

	void SetCamera(const std::shared_ptr<CameraBase>& _camera)
	{
		m_wpCamera = _camera;
	}

	const Math::Matrix GetRotationMatrix()const
	{
		return Math::Matrix::CreateFromYawPitchRoll(
			DirectX::XMConvertToRadians(m_DegAng.y),
			DirectX::XMConvertToRadians(m_DegAng.x),
			DirectX::XMConvertToRadians(m_DegAng.z));
	}

	const Math::Matrix GetRotationYMatrix() const
	{
		return Math::Matrix::CreateRotationY(
			DirectX::XMConvertToRadians(m_DegAng.y));
	}

	const Math::Vector3 GetDir()
	{
		return m_moveDir;
	}

	void SetWeapon(const std::shared_ptr<WeaponBase>& weapon)
	{
		m_wpWeapon = weapon;
	}

	void UpdateRotateByMouse();
private:

	//カメラ情報
	std::weak_ptr<CameraBase> m_wpCamera;

	//ワールド座標
	Math::Vector3 m_pos = Math::Vector3::Zero;
	
	//進行方向（ベクトルの向き）
	Math::Vector3 m_moveDir = Math::Vector3::Zero;

	//武器
	std::weak_ptr<WeaponBase> m_wpWeapon;

	Math::Vector3 m_WprldRot = Math::Vector3::Zero;

	const float m_moveSpeed = 0.4f;

	//プレイヤー座標補正
	const float m_adjusHeight = 10.f;//10

	//ジャンプ力
	const float m_jumpPow = 1.f;
	//キーフラグ
	bool m_jumpKeyFlg = false;
	bool m_leftKeyFlg = false;
	bool m_rightKeyFlg= false;

	//重力
	const float m_gravityPow = 0.04f;
	float m_gravity = 0.0f;

	// カメラ回転用角度
	Math::Vector3				m_DegAng = Math::Vector3::Zero;
	
	// カメラ回転用マウス座標の原点
	POINT						m_FixMousePos{};

};
