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

	// Update/Render�� ��� Scene�� ���Ƽ�, �׳� �θ𿡼� ������
	void Update();
	void Render(HDC _dc);

	virtual void Enter() = 0; // �ش� Scene���� ���� �� ȣ��
	virtual void Exit() = 0; // �ش� Scene���� Ż�� �� ȣ��

protected: // �ڽĿ��� �ʿ��� ����
	// Inline ó�� (ȣ�� ��� ����)
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

public:
	CScene();
	virtual ~CScene();
};

