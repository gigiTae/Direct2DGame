#pragma once

/// <summary>
/// =����׿뵵=
/// ������Ʈ ���̹��� ���ִ� ���� Ŭ����
/// �̱��� ���� ���
/// </summary>
class NamingManager
{
public:
	static NamingManager* GetInstance();
	static void Finalize();
private:
	static NamingManager* m_instance;

private:
	NamingManager() = default;
	~NamingManager();
public:
	const string GenerateName(const string& _name);

private:
	// �̸��������� �ʿ� ������ key : ������Ʈ �̸� value : ������Ʈ ���� Ƚ��
	map<const string, int> m_nameInfo;

};