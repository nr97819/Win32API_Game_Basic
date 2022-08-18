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
	, m_pCollider(nullptr) // �������� ���� �Ҵ� (��������� ���� ���� �� ���� �� �ϳ�)
	, m_pAnimator(nullptr) // ���ó� ::���� ����:: ����̴�.
	, m_bAlive(true) // ó���� ������ true (���� ����������Ƿ�)
{
	// Collider���� ��ġ�� �ʴ� ��������ڸ� �����ߴ� ���� �̿�
	if (nullptr != _origin.m_pCollider) // ������ Collider�� ������ ���� ��� ���� ����
	{
		m_pCollider = new CCollider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this; // ����
	}

	if (nullptr != _origin.m_pAnimator) // ������ Animator�� ������ ���� ��� ���� ����
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this; // ����
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
	// ���� ��ġ�� vDiff�� ������ [vRenderPos]�� CCamera�� ���� ��� �´�.)
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos); // m_vPos : ���� Obj�� ��ġ

	// �׸��� (vRenderPos : vDiff�� ���� ��ġ)
	Rectangle(_dc
		, int(vRenderPos.x - m_vScale.x / 2.f)
		, int(vRenderPos.y - m_vScale.y / 2.f)
		, int(vRenderPos.x + m_vScale.x / 2.f)
		, int(vRenderPos.y + m_vScale.y / 2.f)
	);

	// Component ������
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
	// Collider ������
	if (nullptr != m_pCollider)
	{
		m_pCollider->Render(_dc);
	}

	// Animator ������
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->Render(_dc);
	}
}