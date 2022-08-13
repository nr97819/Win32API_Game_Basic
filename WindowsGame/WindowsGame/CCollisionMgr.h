#pragma once
 

class CCollider;

union COLLIDER_ID
{
	// �뵵 : ���� ������ �浹 ������ ���� [������ ��]�� ���
	// �� 8����Ʈ�� ũ�⸦ ���� �ڷ��� (union�� Ư��)
	// UINT * 2�� �аų�, LONGLONG �ϳ��� ���� �� �ִ�. (�޸� �б� ����� �ΰ��� ��� ����)
	struct
	{
		UINT iLeft;
		UINT iRight;
	};
	ULONGLONG ID;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr);
private:
	map<ULONGLONG, bool>		m_mapColInfo;						// �浹ü ���� ���� ������ �浹 ����
	UINT					m_arrCheck[(UINT)GROUP_TYPE::END];	// Group ���� �浹 üũ Matrix

public:
	//void Init();
	void Update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }
	// uint(4bytes) * 32���� 0���� �ʱ�ȭ

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight); // �浹 ������ ���۵� �� �׷� �� Object�� ������ �� ����
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};

