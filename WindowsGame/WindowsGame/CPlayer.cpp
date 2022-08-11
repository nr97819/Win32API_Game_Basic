#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"

#include "CMissile.h"
#include "CScene.h"


CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	// 플레이어 상,하,좌,우 이동
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT;
	}

	SetPos(vPos);

	// 미사일 발사
	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// 미사일 생성 및 초기화
	CMissile* pMissile = new CMissile();
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(true);
	
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}

//void CPlayer::Render(HDC _dc)
//{
//}