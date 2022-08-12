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
		// ������ �Ⱦ��Ƿ� iRow���͸� ������ �ȴ�. (ǥ ���¸� ����� �����ؾ� �Ѵ�.)
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				// �׻� ���� ���� ������ (�츮�� ������ Collision ǥ�� �׷��� �Ǿ������Ƿ�)
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// (*����) �ٽ� ���������� ����� ������, const &�� �ٿ���߸� original �״�θ� ������ �� �ִ�.
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// Collider ������Ʈ�� ���ٸ� ������ Pass
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// Collider ������Ʈ�� ���ٸ� ������ Pass
			if (nullptr == vecRight[i]->GetCollider())
				continue;

			// ���� �׷��� �ڽŰ��� �񱳸� �����Ѵ�. (�����̹Ƿ�, �ּҰ� ���� ��� ����)
			if (vecLeft[i] == vecRight[j])
				continue;

			// <�浹 ó��>
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

	// �� ���� ���� Group Ÿ���� ������, (�迭 index)
	// �� ū ���� Group Ÿ���� ���� �����ؾ� �Ѵ�. (UINT�� bit)

	// �� ���� ���� iRow�� �������� �������ش�.
	UINT iRow = (UINT)_eLeft; // �迭 index
	UINT iCol = (UINT)_eRight; // UINT�� bits
	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	// 1�� column�� ����ŭ(�ִ� 32bit) ���� shift������ �ؼ�, 
	// �� ���� �ش� iRow�� UINT�� ���ҿ� OR �������� �ִ´�.
	if (m_arrCheck[iRow] & (1 << iCol))
	{
		// ���� �̹� Check �Ǿ� �־��ٸ�, Uncheck ���·� toggle �����ش�.
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		// ���ϴ� �κп� Check �Ϸ�
		m_arrCheck[iRow] |= (1 << iCol);
	}
}
