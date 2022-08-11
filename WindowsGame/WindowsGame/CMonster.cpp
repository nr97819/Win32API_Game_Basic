#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"

CMonster::CMonster()
	: m_vCenterPos{}
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
{
}

CMonster::~CMonster()
{
}

void CMonster::Update()
{
	// ���� ��, �� �̵�
	Vec2 vCurPos = GetPos();

	vCurPos.x += fDT * m_fSpeed * m_iDir;

	// Max �Ÿ��� ���� ���, ���� ��ȯ �� ����
	float fDist = abs(vCurPos.x - m_vCenterPos.x) - m_fMaxDistance;
	if (0.f < fDist)
	{
		// ���� ��ȯ
		m_iDir *= -1;

		// �ʰ��ϰ� �� ���� ������ ���� ���� (�ٲ� �������� �ΰ�)
		vCurPos.x += fDist * m_iDir;
	}

	SetPos(vCurPos);
}