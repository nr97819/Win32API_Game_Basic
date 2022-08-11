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
	// Object의 위치를 따라가도록 설정 (그림자가 주인을 따라간다.)
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;
}

void CCollider::Render(HDC _dc)
{
	// 임시 객체 생성 (지역 객체를 함수만 쓰는 용도로 생성하는 방법)
	// (*) 생성자를 함수처럼 쓰는 것
	SelectGDI selecePen(_dc, PEN_TYPE::GREEN);
	SelectGDI selectBrush(_dc, BRUSH_TYPE::HOLLOW);
	// 객체명 없으면 바로 소멸시켜버리므로, 이름도 줘야 함
	// HPEN, HBRUSH의 해제 또한 SelectGDI()의 소멸자에서 해주므로 편리하다.

	Rectangle(_dc
		, int(m_vFinalPos.x - (m_vScale.x / 2.f))
		, int(m_vFinalPos.y - (m_vScale.y / 2.f))
		, int(m_vFinalPos.x + (m_vScale.x / 2.f))
		, int(m_vFinalPos.y + (m_vScale.y / 2.f)));
}
