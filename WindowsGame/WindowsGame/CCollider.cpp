#include "pch.h"
#include "CCollider.h"

#include "CObject.h"
#include "CCore.h"

#include "SelectGDI.h"

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_vOffsetPos{}
	, m_vFinalPos{}
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
}

void CCollider::Render(HDC _dc)
{
	// �ӽ� ��ü ���� (���� ��ü�� �Լ��� ���� �뵵�� �����ϴ� ���)
	// (*) �����ڸ� �Լ�ó�� ���� ��
	SelectGDI selecePen(_dc, PEN_TYPE::GREEN);
	SelectGDI selectBrush(_dc, BRUSH_TYPE::HOLLOW);
	// ��ü�� ������ �ٷ� �Ҹ���ѹ����Ƿ�, �̸��� ��� ��
	// HPEN, HBRUSH�� ���� ���� SelectGDI()�� �Ҹ��ڿ��� ���ֹǷ� ���ϴ�.

	Rectangle(_dc
		, int(m_vFinalPos.x - (m_vScale.x / 2.f))
		, int(m_vFinalPos.y - (m_vScale.y / 2.f))
		, int(m_vFinalPos.x + (m_vScale.x / 2.f))
		, int(m_vFinalPos.y + (m_vScale.y / 2.f)));
}
