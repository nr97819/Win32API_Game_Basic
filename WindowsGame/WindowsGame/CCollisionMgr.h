#pragma once


class CCollider;

class CCollisionMgr
{
	SINGLE(CCollisionMgr);
private:
	// Group ���� �浹 üũ Matrix
	UINT		m_arrCheck[(UINT)GROUP_TYPE::END];



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

