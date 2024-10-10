#pragma once

class GameScene;

class AnimationCamera :public KdGameObject
{
public:

	AnimationCamera() {}
	virtual ~AnimationCamera() {}

	void Update()override;
	void Init()override;

	void SetAnimationInfo(GameScene* scene, const std::shared_ptr<KdGameObject>& start, const std::shared_ptr<KdGameObject>& end, float spd = 0.01f);

private:

	GameScene* m_pNowScene = nullptr;

	// スタート地点とゴール地点のオブジェクト
	std::weak_ptr<KdGameObject> m_wpStart;
	std::weak_ptr<KdGameObject> m_wpEnd;

	// 進行度(0 ～ 1)
	float m_progress = 0.0f;

	// 進行スピード
	float m_speed = 0.01f;
};