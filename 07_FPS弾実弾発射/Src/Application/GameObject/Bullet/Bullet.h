#pragma
class Bullet : public KdGameObject
{
public:
	Bullet() {};
	~Bullet() override {};

	void Update()override;
	void DrawLit()override;

	void Init()override;

	void Shot(Math::Vector3 _pos,Math::Vector3 _dir);
private:

	//モデル情報
	std::shared_ptr<KdModelWork> m_spModel = nullptr;

	Math::Matrix m_rotBulletMat=Math::Matrix::Identity;

	Math::Vector3 m_pos = {};

	Math::Vector3 m_moveDir = {};

	float m_moveSpeed = 1.f;

};