#include "GameProcessPCH.h"
#include "ResourceManager.h"
#include "Texture.h"

ResourceManager::ResourceManager()
	:m_d2DRenderer(nullptr)
{

}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::Initalize(D2DRenderer* _d2DRenderer)
{
	m_d2DRenderer = _d2DRenderer;
}

void ResourceManager::Finalize()
{

}

Texture* ResourceManager::LoadTexture(const wstring& _key, const wstring& _filePath)
{
	auto iter = m_textures.find(_key);

	// �̹� ������ �ؽ�ó�� ��쿡 ������ �ؽ�ó��ȯ
	if ( iter == m_textures.end())
	{
		return iter->second;
	}

	// ���ο� �ؽ�ó �ε�
	ID2D1Bitmap* bitmap = nullptr;
	assert(m_d2DRenderer->LoadBitMap(_filePath.c_str(), bitmap)
		&& !(L"��Ʈ�� �ҷ����� ����"));

	Texture* texture = new Texture();
	texture->SetBitmap(bitmap);
	texture->SetKey(_key);
	texture->SetRelativePath(_filePath);

	m_textures.insert(make_pair(_key, texture));
}
