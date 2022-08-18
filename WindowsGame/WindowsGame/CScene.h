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

	// 자식이어도, Tile의 X, Y 값을 마음대로 변경할 수 있다면, 설계가 크게 꼬이게 되므로 prviate
	UINT				m_iTileX; // 타일 가로 count
	UINT				m_iTileY; // 타일 세로 count

public:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	UINT GetTileX() { return m_iTileX; }
	UINT GetTileY() { return m_iTileY; }

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

	// 해당 Group 벡터의 원본을 넘겨줘야 한다 (참조 & 로 return 해주는 것에 주의)
	// 원본인 만큼, 훼손하면 안되므로 const 키워드 적용
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }

	// Group을 지정하면, 해당 Group의 모든 Object들을 일괄 삭제해주는 함수 (부모에 정의한 이유)
	void DeletGroup(GROUP_TYPE _eTarget);
	void DeleteAll(); // 모든 Group즉, 모든 Object 삭제

	void CreateTile(UINT _iXCount, UINT _iYCount);

public:
	CScene();
	virtual ~CScene();
};

