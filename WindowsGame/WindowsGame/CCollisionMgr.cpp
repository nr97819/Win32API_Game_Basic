#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"


CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

//void CCollisionMgr::Init()
//{
//}

void CCollisionMgr::Update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		// 절반은 안쓰므로 iRow부터만 읽으면 된다. (표 형태를 제대로 이해해야 한다.)
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				// 항상 작은 값이 좌측에 (우리가 구성한 Collision 표가 그렇게 되어있으므로)
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// (*주의) 다시 지역변수에 담아줄 때에도, const &를 붙여줘야만 original 그대로를 가져올 수 있다.
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// Collider 컴포넌트가 없다면 빠르게 Pass
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// Collider 컴포넌트가 없다면 빠르게 Pass
			if (nullptr == vecRight[i]->GetCollider())
				continue;

			// 같은 그룹의 자신과의 비교를 방지한다. (원본이므로, 주소가 같은 경우 예외)
			if (vecLeft[i] == vecRight[j])
				continue;

			// <충돌 처리>
			if (IsCollision(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider()))
			{

			}
			else
			{

			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{


	return false;
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	/*
		 -------------------------
	|    31, 30, 29, ... , 2, 1, 0
	| 0
	| 1
	| 2
	| ...
	| 29
	| 30
	| 31
	*/

	// 더 작은 값의 Group 타입을 행으로, (배열 index)
	// 더 큰 값의 Group 타입을 열로 설정해야 한다. (UINT의 bit)

	// 더 작은 값이 iRow에 들어오도록 조정해준다.
	UINT iRow = (UINT)_eLeft; // 배열 index
	UINT iCol = (UINT)_eRight; // UINT의 bits
	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	// 1을 column의 값만큼(최대 32bit) 좌측 shift연산을 해서, 
	// 그 값을 해당 iRow의 UINT형 원소에 OR 연산으로 넣는다.
	if (m_arrCheck[iRow] & (1 << iCol))
	{
		// 만약 이미 Check 되어 있었다면, Uncheck 상태로 toggle 시켜준다.
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		// 원하는 부분에 Check 완료
		m_arrCheck[iRow] |= (1 << iCol);
	}
}
