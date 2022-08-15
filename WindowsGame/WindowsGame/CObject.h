#pragma once


class CCollider;
class CAnimator;

// 모든 Object들의 부모 역할 (사용될 목적 X)
class CObject
{
private:
	wstring			m_strName;

	Vec2			m_vPos;
	Vec2			m_vScale;

	// Component
	CCollider*		m_pCollider;
	CAnimator*		m_pAnimator;

	bool			m_bAlive;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; };
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; };
	void SetName(const wstring& _strName) { m_strName = _strName; };

	Vec2 GetPos() { return m_vPos; };
	Vec2 GetScale() { return m_vScale; };
	const wstring& GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }

	bool IsDead() { return !m_bAlive; }

	void CreateCollider();

	virtual void OnCollision(CCollider* _pOther) {}
	virtual void OnCollisionEnter(CCollider* _pOther) {}
	virtual void OnCollisionExit(CCollider* _pOther) {}

private:
	// 함부로 Object를 죽이지 못하도록 private 설정
	void SetDead() { m_bAlive = false; }

public:
	virtual void Update() = 0;
	virtual void FinalUpdate() final; // 오버라이딩 방지
	virtual void Render(HDC _dc);

	// 컴포넌트 따로 render
	void component_render(HDC _dc);

	virtual CObject* Clone() = 0;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

	// Object 삭제를 위해 EventMgr에서는 접근 허용
	friend class CEventMgr;
};

