#pragma once


class CCollider;

class CCollisionMgr
{
	SINGLE(CCollisionMgr);
private:
	// Group 간의 충돌 체크 Matrix
	UINT		m_arrCheck[(UINT)GROUP_TYPE::END];



public:
	//void Init();
	void Update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset() { memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }
	// uint(4bytes) * 32개를 0으로 초기화

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight); // 충돌 검증이 시작될 두 그룹 간 Object들 본격적 비교 시작
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};

