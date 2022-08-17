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
	// Texture �ε�
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\panda.bmp");

	// Collider ������Ʈ ����
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 5.f));
	GetCollider()->SetScale(Vec2(40.f, 40.f)); // Collider�� ũ�⵵ �������ش�.

	// Animator ������Ʈ ����
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\character_link.bmp"); // Texture �ε�
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex
									, Vec2(0.f, 280.f), Vec2(60.f, 65.f), Vec2(60.f, 0.f), 0.05f, 10);

	// �ش� Key�� ���� animation�� map���� find()�� ��, Play �Ѵ�.
	// component_render() ȣ��� ��, m_pCurAnim->Render(_dc);�� ȣ��Ǹ鼭 ��� �ȴ�.
	GetAnimator()->Play(L"WALK_DOWN", true);

	CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");
	for (UINT i = 0; i < pAnim->GetMaxFrame(); ++i)
	{
		pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f); // y�� 20��ŭ �̵��ϵ��� offset �� ����
	}
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
	// �÷��̾� ��,��,��,�� �̵�
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

	// �̻��� �߻�
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

	// ����Ÿ(RGB(255, 0, 255)) ���� Transparent ó�� + BitBlt �ϴ� �Լ�
	// (���̺귯�� ������ ����� ��� ������ �Լ�)
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


	// Component ������ -> Render()�� �������̵� �ؼ�, component_render()�� ���� ����� ��
	component_render(_dc);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	// �̻��� ���� �� �ʱ�ȭ
	CMissile* pMissile = new CMissile();
	pMissile->SetName(L"Missile_Player"); // �̻��� �̸� �ο�
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f, -1.f)); // �� �������� �߻�
	// �� ������, ���߿� �̺�Ʈ ���� �����ϸ� �ȴ�. (������ �ϴ� �н�)

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
}