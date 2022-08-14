#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"
#include "CCollisionMgr.h"


CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Enter()
{
	// Player �߰�
	CObject* pObj;
	pObj = new CPlayer();
	pObj->SetPos(Vec2(300.f, 300.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);


	// Monster �߰�
	UINT iMonCount = 5;
	float fMoveDist = 0.f;
	float fObjScale = 50.f;

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / float(iMonCount - 1);

	CMonster* pMonsterObj = nullptr;
	for (UINT i = 0; i < iMonCount; ++i)
	{
		pMonsterObj = new CMonster();
		pMonsterObj->SetName(L"Monster");
		pMonsterObj->SetPos(Vec2(fMoveDist + (fObjScale / 2) + (i * fTerm), 50.f));
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDistance(fMoveDist);
		AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	}

	// �浹 ����
	// � Player �׷�� � Monster �׷� ���� �浹 üũ���� ����
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);		// PLAYER <=> MONSTER
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER); // MONSTER <=> PROJ_PLAYER

	// 32�� ������ �׷��� �����ϹǷ� 32 * 32 �̴�.
	// �� �׷��� �浹�� ���θ� 1�� 0���� ǥ���ϹǷ� (32 * 32 * 1) bits �̴�. => �迭�� ǥ��
	// (*) ��, 4����Ʈ ������ 32�� �ִ� ���̴�. (������ ������� �ʴ´�.)
}

void CScene_Start::Exit()
{
	// �����ߴ� ��� CheckGroup ����
	CCollisionMgr::GetInst()->Reset();

}