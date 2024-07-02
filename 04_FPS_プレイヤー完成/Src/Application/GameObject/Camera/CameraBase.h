#pragma once

class Player;

class CameraBase : public KdGameObject
{
public:
	CameraBase() {}
	virtual ~CameraBase()override {}

	void Init()override;
	void Update()override;
	void PreDraw()override;

	void SetTarget(const std::shared_ptr<Player>& target);

	// 「絶対変更しません！見るだけ！」な書き方
	const std::shared_ptr<KdCamera>& GetCamera() const
	{
		return m_spCamera;
	}

	// 「中身弄るかもね」な書き方
	std::shared_ptr<KdCamera> WorkCamera() const
	{
		return m_spCamera;
	}

private:

protected:

	std::shared_ptr<KdCamera>	m_spCamera = nullptr;
	std::weak_ptr<Player>	m_wpTarget;

	Math::Matrix m_mLocalPos = Math::Matrix::Identity;
	Math::Matrix m_mRotation = Math::Matrix::Identity;
};