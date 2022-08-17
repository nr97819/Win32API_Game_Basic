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
	// 만약 target을 가졌다면, 해당 target이 LookAt 위치가 된다.
	if (nullptr != m_pTargetObj)
	{
		// Dead 상태에 대한 target 참조 해제 처리
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

	// 보고있는 위치 - 중심 위치
	m_vDiff = m_vLookAt - vCenter;
}
