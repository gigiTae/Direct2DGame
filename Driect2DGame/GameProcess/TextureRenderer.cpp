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
	/// textKey¿Ã æ¯¿Ω
	if (m_textKey.empty())
		return;

	Transform* transform = GetComponent<Transform>();
	
	Vector2 position = transform->GetPosition() + m_offset;
	float rotation = transform->GetRotation();

	_d2DRenderer->DrawBitMap(m_textKey, position, rotation, m_alpha);
}
