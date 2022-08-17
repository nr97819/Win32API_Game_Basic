#pragma once


class CObject;

class CCamera
{
	SINGLE(CCamera)
private:
	Vec2			m_vLookAt;		// ī�޶� ���� ��ġ
	CObject*		m_pTargetObj;	// ī�޶� target ������Ʈ

	Vec2			m_vDiff;		// �ػ� �߽���ġ��, ī�޶� LookAt ��ġ ���� ����(diff) ��

public:
	void SetLookAt(Vec2 _vLook) { m_vLookAt = _vLook; }
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }

	// Object�� ��ġ - vDiff ��
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }

public:
	void Update();

private:
	void CallDiff();
};

