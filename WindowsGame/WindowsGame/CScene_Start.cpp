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
	// �θ� Ŭ���� (CScene) ���� ����Լ��� ȣ��
	CScene::Update(); // ������ ���

	// Enter Ű�� ������, Tool ������ ��ȯ (�̵�)
	if (KEY_TAP(KEY::ENTER))
	{
		// Event�� �̺�Ʈ�� ����ϴ� "���� �Լ�"�� ȣ��
		ChangeScene(SCENE_TYPE::TOOL);
	}

	// ���콺 Ŭ�� ��, �ش� ��ġ�� Player �̵� (smooth ���� ���� �׽�Ʈ)
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		
		CCamera::GetInst()->SetLookAt(vLookAt);
	}
}

void CScene_Start::Enter()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	// Player �߰�
	CObject* pObj;
	pObj = new CPlayer();
	pObj->SetPos(Vec2(300.f, 300.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	// Clone �� ���ο� Player
	/*CObject* pOtherPlayer = pObj->Clone();
	pOtherPlayer->SetPos(Vec2(350.f, 350.f));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);*/


	/************************/
	/*		Camera ����		*/
	/************************/
	// Camera�� �ʱ� LookAt ����
	CCamera::GetInst()->SetLookAt(vResolution / 2.f); // �ػ��� ���߾��� default�� �ٶ󺸰� ���� (�⺻ ����)

	// Camera�� Ÿ�� Object�� Player�� ���� (����ٴϵ��� ����)
	//CCamera::GetInst()->SetTarget(pObj);


	// Monster �߰�
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
	/*		Collision ����		*/
	/****************************/
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

	// �����ϴ� ��� Object ����
	DeleteAll();
}