#pragma once

class CObject;

// ��� Scene���� �θ� ���� (���� ���� X)
class CScene
{
private:
	// �پ��� �׷��� Object���� ����� �� �׷캰 ������ Vector�� ��� ����
	// Object���� ������ ���� Vector��, �ٵ� �� Vector���� 32�� (�迭)
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName; // Scene ���� �̸�

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

public:
	CScene();
	virtual ~CScene();

public:
	void Init();
};

