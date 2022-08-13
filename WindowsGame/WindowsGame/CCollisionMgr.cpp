#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"


CCollisionMgr::CCollisionMgr()
	: m_mapColInfo{}
	, m_arrCheck{}
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

	// �ݺ������� ���� �����ϹǷ�, �̸� �����ؼ� ���
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// Collider ������Ʈ�� ���ٸ� ������ Pass
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// Collider ������Ʈ�� ���ٸ� ������ Pass
			if (nullptr == vecRight[j]->GetCollider())
				continue;

			// ���� �׷��� �ڽŰ��� �񱳸� �����Ѵ�. (�����̹Ƿ�, �ּҰ� ���� ��� ����)
			if (vecLeft[i] == vecRight[j])
				continue;

			// ���� �����ϹǷ�, �̸� �����ؼ� ���
			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// �� �浹ü ������ ���� ID �� ���� (�� �浹ü�� ���ؼ��� ���� �� �ִ� ���� ��)
			COLLIDER_ID ID;
			ID.iLeft = pLeftCol->GetID();
			ID.iRight = pRightCol->GetID();
			
			// �� ������ �浹�ߴ��� ����(����)�� find()�� �˻�
			iter = m_mapColInfo.find(ID.ID);

			// �ƿ� map�� ��ϵ� �ȵƾ��� �浹������ false�� �� ���� insert
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID); // iter�� �ޱ� ����, ���� �� �ٷ� find()
			}

			// [�浹 ó��]
			// ���� �浹 ��
			if (IsCollision(pLeftCol, pRightCol))
			{
				// ���� �����ӵ� �浹
				if (iter->second) // true ����
				{
					// vecLeft[i]�� ������ �浹������ (vecRight[i]) ���ڷ� �־��ش�.
					pLeftCol->OnCollision(pRightCol);
					pRightCol->OnCollision(pLeftCol);
				}
				// ���� �������� �浹 �� �� (*��, �浹 ���� ����)
				else
				{
					pLeftCol->OnCollisionEnter(pRightCol);
					pRightCol->OnCollisionEnter(pLeftCol);

					// "����" �������� ���� "����" �������� true�� ����
					iter->second = true;
				}
			}
			else
			{
				// ���� �����ӿ��� �浹 (*��, �浹 ���� ����)
				if (iter->second) // true ����
				{
					// vecLeft[i]�� ������ �浹������ (vecRight[i]) ���ڷ� �־��ش�.
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);

					// "����" �������� ���� "����" �������� false�� ����
					iter->second = false;
				}
				// ���� �����ӵ� �浹 �� ��
				else
				{
					// �ƹ��͵� �� ��
				}
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();

	// �� Collision�� ������ �����ִٸ� true ��ȯ
	if (abs(vLeftPos.x - vRightPos.x) < (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vLeftPos.y - vRightPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}

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
