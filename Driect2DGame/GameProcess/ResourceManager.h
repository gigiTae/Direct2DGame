#pragma once


class Texture;

/// <summary>
/// 필요한 리소스들을 관리하는 매니져이다.
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

	/// 리소스의 키값으로 텍스처들을 불러온다.
	map<wstring, Texture*> m_textures;
};

