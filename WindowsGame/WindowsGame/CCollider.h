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

	UINT			m_iID;			// 각각의 Collider들은 고유의 ID를 반드시 갖는다. (누구와 누가 충돌했는지 확인용)
	int				m_iCol;

public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

	Vec2 GetFinalPos() { return m_vFinalPos; }

	CObject* GetObj() { return m_pOwner; }

	UINT GetID() { return m_iID; }

public:
	void FinalUpdate();
	void Render(HDC _dc);

public:
	// 충돌 중인 경우, 호출되는 함수
	void OnCollision(CCollider* _pOther);
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

	// 대입연산자 쓸일은 없지만, 실수로 호출하면 ID값 중복 등 문제가 생기므로, 해당 함수 명시적 delete
	CCollider& operator = (CCollider& _origin) = delete;

public:
	CCollider();
	CCollider(const CCollider& _origin); // 복사생성자 재정의 (ID값 중복 방지)
	~CCollider();

	friend class CObject;
};

