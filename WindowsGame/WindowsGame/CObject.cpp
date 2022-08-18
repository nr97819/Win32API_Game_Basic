#include "pch.h"
#include "CObject.h"

#include "CCollider.h"
#include "CAnimator.h"


CObject::CObject()
	: m_strName{}
	, m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_bAlive(true)
{
}

CObject::CObject(const CObject& _origin)
	: m_strName(_origin.m_strName)
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_pCollider(nullptr) // 본문에서 새로 할당 (복사생성자 별도 정의 한 이유 중 하나)
	, m_pAnimator(nullptr) // 역시나 ::깊은 복사:: 대상이다.
	, m_bAlive(true) // 처음엔 무조건 true (새로 만들어졌으므로)
{
	// Collider에서 겹치지 않는 복사생성자를 구현했던 것을 이용
	if (nullptr != _origin.m_pCollider) // 원본이 Collider를 가지고 있을 경우 새로 제공
	{
		m_pCollider = new CCollider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this; // 연결
	}

	if (nullptr != _origin.m_pAnimator) // 원본이 Animator를 가지고 있을 경우 새로 제공
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this; // 연결
	}
}

CObject::~CObject()
{
	if (nullptr != m_pCollider)
	{
		delete m_pCollider;
		m_pCollider = nullptr;
	}

	if (nullptr != m_pAnimator)
	{
		delete m_pAnimator;
		m_pAnimator = nullptr;
	}
}

void CObject::FinalUpdate()
{
	if (m_pCollider)
		m_pCollider->FinalUpdate();

	if (m_pAnimator)
		m_pAnimator->FinalUpdate();
}

void CObject::Render(HDC _dc)
{
	// 실제 위치에 vDiff를 적용한 [vRenderPos]를 CCamera로 부터 얻어 온다.)
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos); // m_vPos : 실제 Obj의 위치

	// 그리기 (vRenderPos : vDiff로 계산된 위치)
	Rectangle(_dc
		, int(vRenderPos.x - m_vScale.x / 2.f)
		, int(vRenderPos.y - m_vScale.y / 2.f)
		, int(vRenderPos.x + m_vScale.x / 2.f)
		, int(vRenderPos.y + m_vScale.y / 2.f)
	);

	// Component 렌더링
	component_render(_dc);
}

void CObject::CreateCollider()
{
	m_pCollider = new CCollider();
	m_pCollider->m_pOwner = this;
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator();
	m_pAnimator->m_pOwner = this;
}

void CObject::component_render(HDC _dc)
{
	// Collider 렌더링
	if (nullptr != m_pCollider)
	{
		m_pCollider->Render(_dc);
	}

	// Animator 렌더링
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->Render(_dc);
	}
}