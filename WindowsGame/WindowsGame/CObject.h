#pragma once


class CCollider;
class CAnimator;

// ��� Object���� �θ� ���� (���� ���� X)
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
	// �Ժη� Object�� ������ ���ϵ��� private ����
	void SetDead() { m_bAlive = false; }

public:
	virtual void Update() = 0;
	virtual void FinalUpdate() final; // �������̵� ����
	virtual void Render(HDC _dc);

	// ������Ʈ ���� render
	void component_render(HDC _dc);

	virtual CObject* Clone() = 0;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

	// Object ������ ���� EventMgr������ ���� ���
	friend class CEventMgr;
};

