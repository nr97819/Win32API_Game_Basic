#pragma once


class CObject;

class CCollider
{
private:
	static UINT		g_iNextID;		// ID 발급을 위한 static 변수 (객체 포함 X)

	CObject*		m_pOwner;		
	Vec2			m_vOffsetPos;	// Owner의 vCurPos로부터의 상대적인 위치 (offset)
	Vec2			m_vFinalPos;	// finalupdate에서 매 프레임마다 계산되는 Collider의 최종 위치
	Vec2			m_vScale;		// Collider(충돌체)의 크기

	UINT			m_iID;			// 각각의 Collider들은 고유의 ID를 반드시 갖는다. 
									// (누구와 누가 충돌했는지 검색하기 위해서)

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	void FinalUpdate();
	void Render(HDC _dc);

public:
	CCollider();
	~CCollider();

	friend class CObject;
};

