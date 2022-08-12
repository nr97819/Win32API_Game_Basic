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

	UINT			m_iID;			// ������ Collider���� ������ ID�� �ݵ�� ���´�. 
									// (������ ���� �浹�ߴ��� �˻��ϱ� ���ؼ�)

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

