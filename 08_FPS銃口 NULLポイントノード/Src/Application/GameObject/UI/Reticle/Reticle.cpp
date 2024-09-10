#include "Reticle.h"

void Reticle::Init()
{
	m_tex.Load("Asset/Textures/Reticle.png");
	m_pos = {};
	m_scale = { 1 };
	m_texSize = { 64.0f,64.0f };
	m_color = { 1.0f,1.0f,1.0f,1.0f };
}

void Reticle::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, m_pos.x, m_pos.y,
		m_texSize.x * m_scale.x, m_texSize.y * m_scale.y,
		nullptr, &m_color);
}
