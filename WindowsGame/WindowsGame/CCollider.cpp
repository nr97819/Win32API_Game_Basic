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
	, m_iID(g_iNextID++) // ID 발급 및 static 값 후위 연산 ++1
{
}

CCollider::CCollider(const CCollider& _origin)
	: m_pOwner(nullptr)			// 소유자 변경되야 하므로, 복사 않고 nullptr로 비워 둠
	, m_vOffsetPos(_origin.m_vOffsetPos)
	//, m_vFinalPos(_origin.m_vFinalPos) // 굳이 복사할 필요는 없음 (매프레임 재계산 되는 값이므로)
	, m_vScale(_origin.m_vScale)
	, m_iID(g_iNextID++)		// ID 값 새로 발급 (중복 방지)
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

void CCollider::OnCollision(CCollider* _pOther)
{

}

void CCollider::OnCollisionEnter(CCollider* _pOther)
{

}

void CCollider::OnCollisionExit(CCollider* _pOther)
{

}
