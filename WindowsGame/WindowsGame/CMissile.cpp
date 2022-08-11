#include "pch.h"
#include "CMissile.h"

#include "CTimeMgr.h"

CMissile::CMissile()
	: m_fTheta(PI / 4.f)
	, m_vDir(Vec2(1.f, 1.f)) // 45���� �ش��ϴ� Vector������ �ʱ�ȭ
{
	// [������ ����ȭ] - (��Ʈ2�� 1�� ����) -> ���� ����� �����ϱ� ����
	// ����ȭ ���� �̿� (�밢���� ���̷� ���� ��, ���� ���Ѵ�)
	m_vDir.Normalize();
	// ����ȭ �Լ� -> ���� ����
}

CMissile::~CMissile()
{
}

void CMissile::Update()
{
	Vec2 vPos = GetPos();

	vPos.x += 600.f * m_vDir.x * fDT;
	vPos.y += 600.f * m_vDir.y * fDT;

	SetPos(vPos);
}

void CMissile::Render(HDC _dc)
{
	// �׸���
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	
	Ellipse(_dc
		, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f)
	);

	SetPos(vPos);
}