#include "GameProcessPCH.h"
#include "TextureRenderer.h"
#include "Transform.h"
#include "GameObject.h"

TextureRenderer::TextureRenderer()
	:Component(CALL_ORDER::RENDERER,typeid(this).name())
	,m_alpha(1.f),m_offset{},m_textKey{}
{

}

TextureRenderer::~TextureRenderer()
{

}

void TextureRenderer::Render(D2DRenderer* _d2DRenderer)
{
	/// textKeyÀÌ ¾øÀ½
	if (m_textKey.empty())
		return;

	Vector2 position = m_transform->GetPosition() + m_offset;
	float rotation = m_transform->GetRotation();

	_d2DRenderer->DrawBitMap(m_textKey, position, rotation, m_alpha);
}

void TextureRenderer::Start()
{
	m_transform = GetComponent<Transform>();

	assert(m_transform);
}
