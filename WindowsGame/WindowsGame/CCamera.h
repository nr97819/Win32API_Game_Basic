#pragma once


class CObject;

class CCamera
{
	SINGLE(CCamera)
private:
	Vec2			m_vLookAt;		// 카메라가 보는 위치
	Vec2			m_vCurLookAt;	// 이전 Pos와 이동하려는 목표 Pos 사이 현재 Pos (보정 위치)
	Vec2			m_vPrevLookAt;	// 카메라가 보는 "직전 프레임" 위치 (smooth 카메라 무빙을 위한 변수)

	CObject*		m_pTargetObj;	// 카메라 target 오브젝트

	Vec2			m_vDiff;		// 해상도 중심위치와, 카메라 LookAt 위치 간의 차이(diff) 값

public:
	void SetLookAt(Vec2 _vLook) { m_vLookAt = _vLook; }
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }

	Vec2 GetLookAt() { return m_vCurLookAt; }

	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }		// realPos -> renderPos (카메라 적용)
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }	// renderPos -> realPos (카메라 미적용)

public:
	void Update();

private:
	void CallDiff();
};

