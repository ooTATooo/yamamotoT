#pragma once

#include"../BaseScene/BaseScene.h"

class CameraBase;

class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() {}

	bool SetCameraTarget(std::weak_ptr<KdGameObject> target);

private:

	// 使用しているカメラ
	std::weak_ptr<CameraBase> m_wpCamera;

	// カメラのターゲットになっているオブジェクトの名前
	std::string m_strCameraTarget = "Robot";

	// カメラのターゲットの変更
	void ChangeCameraTarget();

	// 指定された名前で検索して合致したオブジェクトを返す
	std::shared_ptr<KdGameObject> FindObjectWithName(const std::string& name);

	bool m_keyFlg = false;

	void Event() override;
	void Init() override;
};
