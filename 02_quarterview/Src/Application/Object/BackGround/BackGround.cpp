#include "BackGround.h"

void BackGround::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(m_polygon, m_mWorld);
}

void BackGround::Init()
{
	// 板ポリにテクスチャ(マテリアル)をセット
	m_polygon.SetMaterial("Asset/Textures/BackGround.png");

	// 板ポリのサイズを拡大
	m_polygon.SetScale(200.0f);

	// 板ポリの原点を変更
	m_polygon.SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	// 行列の作成
	m_mWorld = Math::Matrix::CreateTranslation(0, 0, 100);
}
