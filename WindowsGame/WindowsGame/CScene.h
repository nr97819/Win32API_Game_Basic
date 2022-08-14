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

	// 모든 Scene이 Update/Render가 동일하므로 모두 부모(Scene)에서 정의함
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);

	virtual void Enter() = 0; // 해당 Scene으로 진입 시 호출
	virtual void Exit() = 0; // 해당 Scene에서 탈출 시 호출

public:
	// Inline 처리 (호출 비용 절약)
	void AddObject(CObject* _pObj, GROUP_TYPE _eType) 
	{ 
		m_arrObj[(UINT)_eType].push_back(_pObj); 
	}

	// Group을 지정하면, 해당 Group의 모든 Object들을 일괄 삭제해주는 함수 (부모에 정의한 이유)
	void DeletGroup(GROUP_TYPE _eTarget);
	void DeleteAll(); // 모든 Group즉, 모든 Object 삭제

	// 해당 Group 벡터의 원본을 넘겨줘야 한다 (참조 & 로 return 해주는 것에 주의)
	// 원본인 만큼, 훼손하면 안되므로 const 키워드 적용
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }

public:
	CScene();
	virtual ~CScene();
};

