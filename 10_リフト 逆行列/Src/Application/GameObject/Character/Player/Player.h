class CameraBase;
class WeaponBase;
class Lift;

class Player:public KdGameObject
{
public:
	Player() {};
	~Player() override {};

	void Init()override;
	void Update()override;
	void PostUpdate()override;

	void SetCamera(const std::shared_ptr<CameraBase>& _camera)
	{
		m_wpCamera = _camera;
	}

	void SetWeapon(const std::shared_ptr<WeaponBase>& _weapon)
	{
		m_wpWeapon = _weapon;
	}

	void SetRide(const std::shared_ptr<KdGameObject>& _ride)
	{
		m_wpRideObject = _ride;
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

	void UpdateRotateByMouse();

	const Math::Vector3 GetRotateAngle()const { return m_DegAng; }

private:

	//カメラ情報
	std::weak_ptr<CameraBase> m_wpCamera;
	std::weak_ptr<WeaponBase> m_wpWeapon;

	//ワールド座標
	Math::Vector3 m_pos = Math::Vector3::Zero;
	
	//進行方向（ベクトルの向き）
	Math::Vector3 m_moveDir = Math::Vector3::Zero;

	Math::Vector3 m_WprldRot = Math::Vector3::Zero;

	const float m_moveSpeed = 0.5f;

	//プレイヤー座標補正
	const float m_adjusHeight = 10.0f;//10

	//ジャンプ力
	const float m_jumoPow = 1.0f;
	bool m_key = false;
	bool m_leftKeyFlg = false;
	bool m_rightKeyFlg = false;

	//重力
	const float m_gravityPow = 0.04f;
	float m_gravity = 0.0f;

	// 乗り物制御関係
	std::weak_ptr<KdGameObject> m_wpRideObject;	// 乗っているオブジェクト
	Math::Matrix m_localMatFromRideObject;		// 乗っているオブジェクトからのローカル行列

	// カメラ回転用角度
	Math::Vector3				m_DegAng = Math::Vector3::Zero;
	
	// カメラ回転用マウス座標の原点
	POINT						m_FixMousePos{};


	bool keyFlg = false;
	bool camFlg = true;
};
