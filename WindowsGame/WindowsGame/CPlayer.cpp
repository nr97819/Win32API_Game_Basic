#include "pch.h"
#include "CPlayer.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSceneMgr.h"

#include "CMissile.h"
#include "CScene.h"

#include "CPathMgr.h"
#include "CTexture.h"


CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	// Texture 로드
	m_pTex = new CTexture();

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"texture\\panda.bmp";
	m_pTex->Load(strFilePath);
}

CPlayer::~CPlayer()
{
	if (nullptr != m_pTex)
	{
		delete m_pTex;
		m_pTex = nullptr;
	}
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

void CPlayer::Render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();

	/*BitBlt(_dc
		, int(vPos.x - (float)(iWidth / 2.f))
		, int(vPos.y - (float)(iHeight / 2.f))
		, iWidth
		, iHeight
		, m_pTex->GetDC()
		, 0, 0, SRCCOPY);*/

	// 마젠타(RGB(255, 0, 255)) 색상 Transparent 처리 + BitBlt 하는 함수
	// (라이브러리 참조를 해줘야 사용 가능한 함수)
	TransparentBlt(_dc
		, int(vPos.x - (float)(iWidth / 2.f))
		, int(vPos.y - (float)(iHeight / 2.f))
		, iWidth
		, iHeight
		, m_pTex->GetDC()
		, 0, 0
		, iWidth
		, iHeight
		, RGB(255, 0, 255));
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// 미사일 생성 및 초기화
	CMissile* pMissile = new CMissile();
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f)); // 위 방향으로 발사
	
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::DEFAULT);
}