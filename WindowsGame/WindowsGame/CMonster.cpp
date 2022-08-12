#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CCollider.h"


CMonster::CMonster()
	: m_vCenterPos{}
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(60.f, 60.f));
}

CMonster::~CMonster()
{
}

void CMonster::Update()
{
	// 몬스터 좌, 우 이동
	Vec2 vCurPos = GetPos();

	vCurPos.x += fDT * m_fSpeed * m_iDir;

	// Max 거리를 넘은 경우, 방향 전환 및 수복
	float fDist = abs(vCurPos.x - m_vCenterPos.x) - m_fMaxDistance;
	if (0.f < fDist)
	{
		// 방향 전환
		m_iDir *= -1;

		// 초과하게 된 오차 범위에 대한 수복 (바뀐 방향으로 인가)
		vCurPos.x += fDist * m_iDir;
	}

	SetPos(vCurPos);
}
