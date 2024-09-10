#include "Cloud.h"

#include "../../Character/Player/Player.h"

void Cloud::Update()
{
	// ビルボード ・・・ どこから見ても板ポリが正面を向いている

	// 方法１ プレイヤー(カメラ)と同じ回転処理を施す

	Math::Vector3 angle;
	std::shared_ptr<Player> player = m_wpPlayer.lock();
	//if (player)
	//{
	//	angle = player->GetRotateAngle();
	//}

	//Math::Vector3 pos = GetPos();

	//Math::Matrix transMat = Math::Matrix::CreateTranslation(pos);
	//// 常に正面に向いてOKな場合はX軸、Y軸で回転させる
	//// プレイヤー(カメラ)と同じ回転行列を作成自身に適応
	//m_mWorld = Math::Matrix::CreateFromYawPitchRoll(
	//	DirectX::XMConvertToRadians(angle.y),
	//	DirectX::XMConvertToRadians(angle.x),
	//	0.0f
	//);

	//m_mWorld.Translation(pos);

	//Math::Matrix rotMatY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(angle.y));
	//m_mWorld = rotMatY;

	// 方法２
	Math::Matrix playerMat;
	if (player)
	{
		playerMat = player->GetMatrix();
	}

	m_mWorld.Backward(playerMat.Backward());
	m_mWorld.Up(playerMat.Up());
	m_mWorld.Right(playerMat.Right());
}

void Cloud::Init()
{
	if (!m_spPoly)
	{
		m_spPoly = std::make_shared<KdSquarePolygon>();
		m_spPoly->SetMaterial("Asset/Textures/Cloud.png");
	}
}

void Cloud::DrawUnLit()
{
	if (!m_spPoly)return;

	// 加算半透明
	KdShaderManager::Instance().ChangeBlendState(KdBlendState::Add);

	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_spPoly, m_mWorld);

	KdShaderManager::Instance().ChangeBlendState(KdBlendState::Alpha);

	// 加算半透明問題
	// 加算半透明にするオブジェクトは最後に描画しないと透過部分が描画順の問題でバグる
	// 解決の方法としてはZソートで奥から順番に描画するように設計する

	// １不透明なオブジェクトを描画する
	// ２半透明オブジェクト(Zソート済み)を描画する
}
