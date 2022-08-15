#include "pch.h"
#include "CObject.h"

#include "CCollider.h"


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
	if (nullptr != _origin.m_pCollider) // ������ Collider�� �����ϰ� �ִ� ��쿡��, ���� �����ϹǷ� ����ó��
	{
		m_pCollider = new CCollider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this; // ����
	}

	//if (nullptr != _origin.m_pCollider)
	//{
	//	m_pCollider = new CCollider(*_origin.m_pCollider);
	//	m_pCollider->m_pOwner = this; // ����
	//}
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
}

void CObject::Render(HDC _dc)
{
	// �׸���
	Rectangle(_dc
		, int(m_vPos.x - m_vScale.x / 2.f)
		, int(m_vPos.y - m_vScale.y / 2.f)
		, int(m_vPos.x + m_vScale.x / 2.f)
		, int(m_vPos.y + m_vScale.y / 2.f)
	);

	// Component ������
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