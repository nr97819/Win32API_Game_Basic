#pragma once
 

class CCollider;

union COLLIDER_ID
{
	// 용도 : 이전 프레임 충돌 정보를 담은 [고유한 값]을 기록
	// 총 8바이트의 크기를 갖는 자료형 (union의 특성)
	// UINT * 2로 읽거나, LONGLONG 하나로 읽을 수 있다. (메모리 읽기 방식의 두가지 방식 가능)
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
	map<ULONGLONG, bool>		m_mapColInfo;						// 충돌체 간의 이전 프레임 충돌 정보
	UINT					m_arrCheck[(UINT)GROUP_TYPE::END];	// Group 간의 충돌 체크 Matrix

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

