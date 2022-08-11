#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"


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
	AddObject(pObj, GROUP_TYPE::DEFAULT);


	// Monster 추가
	UINT iMonCount = 16;
	float fMoveDist = 25.f;
	float fObjScale = 50.f;

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	float fTerm = (vResolution.x - ((fMoveDist + fObjScale / 2.f) * 2)) / float(iMonCount - 1);

	CMonster* pMonsterObj = nullptr;
	for (UINT i = 0; i < iMonCount; ++i)
	{
		pMonsterObj = new CMonster();
		pMonsterObj->SetPos(Vec2(fMoveDist + (fObjScale / 2) + (i * fTerm), 50.f));
		pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
		pMonsterObj->SetCenterPos(pMonsterObj->GetPos());
		pMonsterObj->SetMoveDistance(fMoveDist);
		AddObject(pMonsterObj, GROUP_TYPE::DEFAULT);
	}
}

void CScene_Start::Exit()
{

}