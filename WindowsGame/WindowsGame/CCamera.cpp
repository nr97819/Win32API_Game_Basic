#include "pch.h"
#include "CCamera.h"

#include "CObject.h"

#include "CCore.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"


CCamera::CCamera()
	: m_vLookAt{}
	, m_vCurLookAt{}
	, m_vPrevLookAt{}
	, m_pTargetObj(nullptr)
	, m_vDiff{}
	, m_fTime(0.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.f)
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

	// 키 입력을 통한, Camera 움직임
	if (KEY_HOLD(KEY::UP))
		m_vLookAt.y -= 500.f * fDT;
	if (KEY_HOLD(KEY::DOWN))
		m_vLookAt.y += 500.f * fDT;
	if (KEY_HOLD(KEY::LEFT))
		m_vLookAt.x -= 500.f * fDT;
	if (KEY_HOLD(KEY::RIGHT))
		m_vLookAt.x += 500.f * fDT;

	// 화면 중앙좌표와, 카메라 LookAt 좌표간의 차이값을 매 프레임마다 계산
	CallDiff();
}

void CCamera::CallDiff()
{
	// 이전 LootAt 과 현재 LookAt의 차이값을 보정해서, 현재의 LookAt 값을 구한다. (smooth 카메라 무빙 적용)

	m_fAccTime += fDT;
	if (m_fTime <= m_fAccTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		// 두 Vec2의 위치를 뺀 값을 이용, 즉, 방향으로 쓰면 된다. (물리 벡터 방향 값)
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;
		m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
	}

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	// 보고있는 위치 - 중심 위치
	m_vDiff = m_vCurLookAt - vCenter; // m_vCurLookAt를 이용하여 계산하는 이유 알고 넘어가기

	// 이전 LookAt을, 현재 LookAt으로 새로 초기화
	m_vPrevLookAt = m_vCurLookAt;


}
