#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CCollider.h"


CMonster::CMonster()
	: m_vCenterPos{}
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
	, m_iHP(5) // ���� 5�� �ߵ𵵷�
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

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		// ���� ��ġ ��Ȳ �ο�
		m_iHP -= 1;

		if(m_iHP <= 0)
			DeleteObject(this);
	}
}