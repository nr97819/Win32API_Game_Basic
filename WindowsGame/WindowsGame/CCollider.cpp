#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"

#include "SelectGDI.h"


UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_vOffsetPos{}
	, m_vFinalPos{}
	, m_vScale{}
	, m_iID(g_iNextID++) // ID �߱� �� static �� ���� ���� ++1
	, m_iCol(0)
{
}

CCollider::CCollider(const CCollider& _origin)
	: m_pOwner(nullptr)			// ������ ����Ǿ� �ϹǷ�, ���� �ʰ� nullptr�� ��� ��
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_vFinalPos(_origin.m_vFinalPos) // ���� ������ �ʿ�� ���� (�������� ���� �Ǵ� ���̹Ƿ�)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++)		// ID �� ���� �߱� (�ߺ� ����)
	, m_iCol(0)
{
}

CCollider::~CCollider()
{
}

void CCollider::FinalUpdate()
{
	// Object�� ��ġ�� ���󰡵��� ���� (�׸��ڰ� ������ ���󰣴�.)
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;

	// iCol ���� ó�� (0���� �۴ٸ� ���� ��Ȳ �߻�)
	assert(0 <= m_iCol);
}

void CCollider::Render(HDC _dc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;
	if (0 < m_iCol)
		ePen = PEN_TYPE::RED;

	// �ӽ� ��ü ���� (���� ��ü�� �Լ��� ���� �뵵�� �����ϴ� ���)
	// (*) �����ڸ� �Լ�ó�� ���� ��
	SelectGDI selecePen(_dc, ePen);
	SelectGDI selectBrush(_dc, BRUSH_TYPE::HOLLOW);
	// ��ü�� ������ �ٷ� �Ҹ���ѹ����Ƿ�, �̸��� ��� ��
	// HPEN, HBRUSH�� ���� ���� SelectGDI()�� �Ҹ��ڿ��� ���ֹǷ� ���ϴ�.

	Rectangle(_dc
		, int(m_vFinalPos.x - (m_vScale.x / 2.f))
		, int(m_vFinalPos.y - (m_vScale.y / 2.f))
		, int(m_vFinalPos.x + (m_vScale.x / 2.f))
		, int(m_vFinalPos.y + (m_vScale.y / 2.f)));
}

void CCollider::OnCollision(CCollider* _pOther)
{

}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{
	++m_iCol;
}

void CCollider::OnCollisionExit(CCollider* _pOther)
{
	--m_iCol;
}
