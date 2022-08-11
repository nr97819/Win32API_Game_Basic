#include "pch.h"
#include "CObject.h"

#include "CCollider.h"

CObject::CObject()
	: m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
{
}

CObject::~CObject()
{
	if (nullptr != m_pCollider)
	{
		delete m_pCollider;
		m_pCollider = nullptr;
	}
}

void CObject::FinalUpdate()
{
	if (m_pCollider)
		m_pCollider->FinalUpdate();
}

void CObject::Render(HDC _dc)
{
	// 그리기
	Rectangle(_dc
		, int(m_vPos.x - m_vScale.x / 2.f)
		, int(m_vPos.y - m_vScale.y / 2.f)
		, int(m_vPos.x + m_vScale.x / 2.f)
		, int(m_vPos.y + m_vScale.y / 2.f)
	);

	// Component 렌더링
	component_render(_dc);
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider();
	m_pCollider->m_pOwner = this;
}

void CObject::component_render(HDC _dc)
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->Render(_dc);
	}
}