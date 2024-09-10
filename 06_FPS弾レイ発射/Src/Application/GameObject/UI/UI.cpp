#include "UI.h"

void UI::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_tex, 0, 0, (int)(m_tex->GetWidth()), (int)(m_tex->GetHeight()), nullptr, nullptr);

}

void UI::Init()
{
	m_tex = std::make_shared<KdTexture>();
	m_tex->Load("Asset/Textures/Reticle.png");
}
