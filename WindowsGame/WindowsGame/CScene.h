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

	// ��� Scene�� Update/Render�� �����ϹǷ� ��� �θ�(Scene)���� ������
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	virtual void Enter() = 0; // �ش� Scene���� ���� �� ȣ��
	virtual void Exit() = 0; // �ش� Scene���� Ż�� �� ȣ��

public:
	// Inline ó�� (ȣ�� ��� ����)
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) 
	{ 
		m_arrObj[(UINT)_eType].push_back(_pObj); 
	}

	// Group�� �����ϸ�, �ش� Group�� ��� Object���� �ϰ� �������ִ� �Լ� (�θ� ������ ����)
	void DeletGroup(GROUP_TYPE _eTarget);
	void DeleteAll(); // ��� Group��, ��� Object ����

	// �ش� Group ������ ������ �Ѱ���� �Ѵ� (���� & �� return ���ִ� �Ϳ� ����)
	// ������ ��ŭ, �Ѽ��ϸ� �ȵǹǷ� const Ű���� ����
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }

public:
	CScene();
	virtual ~CScene();
};

