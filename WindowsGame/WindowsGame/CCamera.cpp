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

	// Ű �Է��� ����, Camera ������
	if (KEY_HOLD(KEY::UP))
		m_vLookAt.y -= 500.f * fDT;
	if (KEY_HOLD(KEY::DOWN))
		m_vLookAt.y += 500.f * fDT;
	if (KEY_HOLD(KEY::LEFT))
		m_vLookAt.x -= 500.f * fDT;
	if (KEY_HOLD(KEY::RIGHT))
		m_vLookAt.x += 500.f * fDT;

	// ȭ�� �߾���ǥ��, ī�޶� LookAt ��ǥ���� ���̰��� �� �����Ӹ��� ���
	CallDiff();
}

void CCamera::CallDiff()
{
	// ���� LootAt �� ���� LookAt�� ���̰��� �����ؼ�, ������ LookAt ���� ���Ѵ�. (smooth ī�޶� ���� ����)

	m_fAccTime += fDT;
	if (m_fTime <= m_fAccTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		// �� Vec2�� ��ġ�� �� ���� �̿�, ��, �������� ���� �ȴ�. (���� ���� ���� ��)
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;
		m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;
	}

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	// �����ִ� ��ġ - �߽� ��ġ
	m_vDiff = m_vCurLookAt - vCenter; // m_vCurLookAt�� �̿��Ͽ� ����ϴ� ���� �˰� �Ѿ��

	// ���� LookAt��, ���� LookAt���� ���� �ʱ�ȭ
	m_vPrevLookAt = m_vCurLookAt;


}
