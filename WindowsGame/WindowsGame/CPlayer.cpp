#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"
#include "CResMgr.h"

#include "CMissile.h"
#include "CScene.h"

#include "CCollider.h"
#include "CAnimator.h"

#include "CTexture.h"
#include "CAnimation.h"


CPlayer::CPlayer()
	//: m_pTex(nullptr)
{
	// Texture 로드
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\panda.bmp");

	// Collider 컴포넌트 생성
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 5.f));
	GetCollider()->SetScale(Vec2(40.f, 40.f)); // Collider의 크기도 지정해준다.

	// Animator 컴포넌트 생성
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\character_link.bmp"); // Texture 로드
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex
									, Vec2(0.f, 280.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.05f, 10);

	// 해당 Key를 가진 animation을 map에서 find()한 뒤, Play 한다.
	// component_render() 호출될 때, m_pCurAnim->Render(_dc);가 호출되면서 출력 된다.
	GetAnimator()->Play(L"WALK_DOWN", true);

	CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");
	for (UINT i = 0; i < pAnim->GetMaxFrame(); ++i)
	{
		pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f); // y축 20만큼 이동하도록 offset 값 조정
	}
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

	// Test
	GetAnimator()->Update();
}

void CPlayer::Render(HDC _dc)
{
	/*int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();*/

	/*BitBlt(_dc
		, int(vPos.x - (float)(iWidth / 2.f))
		, int(vPos.y - (float)(iHeight / 2.f))
		, iWidth
		, iHeight
		, m_pTex->GetDC()
		, 0, 0, SRCCOPY);*/

	// 마젠타(RGB(255, 0, 255)) 색상 Transparent 처리 + BitBlt 하는 함수
	// (라이브러리 참조를 해줘야 사용 가능한 함수)
	/*TransparentBlt(_dc
		, int(vPos.x - (float)(iWidth / 2.f))
		, int(vPos.y - (float)(iHeight / 2.f))
		, iWidth
		, iHeight
		, m_pTex->GetDC()
		, 0, 0
		, iWidth
		, iHeight
		, RGB(255, 0, 255));*/


	// Component 렌더링 -> Render()를 오버라이딩 해서, component_render()도 따로 써줘야 함
	component_render(_dc);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// 미사일 생성 및 초기화
	CMissile* pMissile = new CMissile();
	pMissile->SetName(L"Missile_Player"); // 미사일 이름 부여
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f)); // 위 방향으로 발사
	// 위 내용은, 나중에 이벤트 관련 수정하면 된다. (지금은 일단 패스)

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}