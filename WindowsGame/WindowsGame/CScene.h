#pragma once

class CObject;

// 모든 Scene들의 부모 역할 (사용될 목적 X)
class CScene
{
private:
	// 다양한 그룹의 Object들을 나누어서 각 그룹별 배정된 Vector에 담기 위함
	// Object들을 여러개 담을 Vector들, 근데 이 Vector들이 32개 (배열)
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];
	wstring				m_strName; // Scene 고유 이름

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

public:
	CScene();
	virtual ~CScene();

public:
	void Init();
};

