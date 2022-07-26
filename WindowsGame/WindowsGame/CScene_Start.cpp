#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"
#include "CCollisionMgr.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CCamera.h"


CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::Update()
{
	// 부모 클래스 (CScene) 쪽의 멤버함수를 호출
	CScene::Update(); // 유용한 기술

	// Enter 키가 눌리면, Tool 씬으로 전환 (이동)
	if (KEY_TAP(KEY::ENTER))
	{
		// Event에 이벤트를 등록하는 "전역 함수"를 호출
		ChangeScene(SCENE_TYPE::TOOL);
	}

	// 마우스 클릭 시, 해당 위치로 Player 이동 (smooth 무브 적용 테스트)
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		
		CCamera::GetInst()->SetLookAt(vLookAt);
	}
}

void CScene_Start::Enter()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	// Player 추가
	CObject* pObj;
	pObj = new CPlayer();
	pObj->SetPos(Vec2(300.f, 300.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	// Clone 된 새로운 Player
	/*CObject* pOtherPlayer = pObj->Clone();
	pOtherPlayer->SetPos(Vec2(350.f, 350.f));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);*/


	/************************/
	/*		Camera 설정		*/
	/************************/
	// Camera의 초기 LookAt 설정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f); // 해상도의 정중앙을 default로 바라보게 설정 (기본 설정)

	// Camera의 타겟 Object를 Player로 설정 (따라다니도록 설정)
	//CCamera::GetInst()->SetTarget(pObj);


	// Monster 추가
	UINT iMonCount = 5;
	float fMoveDist = 0.f;
	float fObjScale = 50.f;

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


	/****************************/
	/*		Collision 설정		*/
	/****************************/
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

	// 존재하는 모든 Object 제거
	DeleteAll();
}