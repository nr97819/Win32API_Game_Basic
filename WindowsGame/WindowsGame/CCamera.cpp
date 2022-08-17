#include "pch.h"
#include "CCamera.h"

#include "CObject.h"

#include "CCore.h"

CCamera::CCamera()
	: m_vLookAt{}
	, m_pTargetObj(nullptr)
{
}

CCamera::~CCamera()
{
}

void CCamera::Update()
{
	// ���� target�� �����ٸ�, �ش� target�� LookAt ��ġ�� �ȴ�.
	if (nullptr != m_pTargetObj)
	{
		// Dead ���¿� ���� target ���� ���� ó��
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}
	}
}

void CCamera::CallDiff()
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	// �����ִ� ��ġ - �߽� ��ġ
	m_vDiff = m_vLookAt - vCenter;
}
