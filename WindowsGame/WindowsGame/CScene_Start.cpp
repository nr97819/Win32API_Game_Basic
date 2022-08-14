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
	// Player 추가
	CObject* pObj;
	pObj = new CPlayer();
	pObj->SetPos(Vec2(300.f, 300.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);


	// Monster 추가
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

	// 충돌 지정
	// 어떤 Player 그룹과 어떤 Monster 그룹 간의 충돌 체크할지 결정
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);		// PLAYER <=> MONSTER
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER); // MONSTER <=> PROJ_PLAYER

	// 32개 종류의 그룹이 존재하므로 32 * 32 이다.
	// 각 그룹의 충돌의 여부를 1과 0으로 표현하므로 (32 * 32 * 1) bits 이다. => 배열로 표현
	// (*) 즉, 4바이트 정수가 32개 있는 것이다. (절반은 사용하지 않는다.)
}

void CScene_Start::Exit()
{
	// 설정했던 모든 CheckGroup 해제
	CCollisionMgr::GetInst()->Reset();

}