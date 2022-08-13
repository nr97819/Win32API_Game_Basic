#pragma once


class CObject;

class CCollider
{
private:
	static UINT		g_iNextID;		// ID �߱��� ���� static ���� (��ü ���� X)

	CObject*		m_pOwner;		
	Vec2			m_vOffsetPos;	// Owner�� vCurPos�κ����� ������� ��ġ (offset)
	Vec2			m_vFinalPos;	// finalupdate���� �� �����Ӹ��� ���Ǵ� Collider�� ���� ��ġ
	Vec2			m_vScale;		// Collider(�浹ü)�� ũ��

	UINT			m_iID;			// ������ Collider���� ������ ID�� �ݵ�� ���´�. (������ ���� �浹�ߴ��� Ȯ�ο�)
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
	// �浹 ���� ���, ȣ��Ǵ� �Լ�
	void OnCollision(CCollider* _pOther);
	void OnCollisionEnter(CCollider* _pOther);
	void OnCollisionExit(CCollider* _pOther);

	// ���Կ����� ������ ������, �Ǽ��� ȣ���ϸ� ID�� �ߺ� �� ������ ����Ƿ�, �ش� �Լ� ����� delete
	CCollider& operator = (CCollider& _origin) = delete;

public:
	CCollider();
	CCollider(const CCollider& _origin); // ��������� ������ (ID�� �ߺ� ����)
	~CCollider();

	friend class CObject;
};

