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

	// Update/Render는 모든 Scene이 같아서, 그냥 부모에서 정의함
	void Update();
	void Render(HDC _dc);

	virtual void Enter() = 0; // 해당 Scene으로 진입 시 호출
	virtual void Exit() = 0; // 해당 Scene에서 탈출 시 호출

protected: // 자식에서 필요한 내용
	// Inline 처리 (호출 비용 절약)
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

public:
	CScene();
	virtual ~CScene();
};

