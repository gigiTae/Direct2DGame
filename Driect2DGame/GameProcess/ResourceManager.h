#pragma once


class Texture;

/// <summary>
/// �ʿ��� ���ҽ����� �����ϴ� �Ŵ����̴�.
/// 
/// 2023.07.03
/// </summary>
class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void Initalize(D2DRenderer* _d2DRenderer);
	void Finalize();


public:
	Texture* LoadTexture(const wstring& _key, const wstring& _filePath);

private:
	D2DRenderer* m_d2DRenderer;

	/// ���ҽ��� Ű������ �ؽ�ó���� �ҷ��´�.
	map<wstring, Texture*> m_textures;
};

