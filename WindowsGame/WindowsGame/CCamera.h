#pragma once


class CObject;

class CCamera
{
	SINGLE(CCamera)
private:
	Vec2			m_vLookAt;		// ī�޶� ���� ��ġ
	Vec2			m_vCurLookAt;	// ���� Pos�� �̵��Ϸ��� ��ǥ Pos ���� ���� Pos (���� ��ġ)
	Vec2			m_vPrevLookAt;	// ī�޶� ���� "���� ������" ��ġ (smooth ī�޶� ������ ���� ����)

	CObject*		m_pTargetObj;	// ī�޶� target ������Ʈ
	Vec2			m_vDiff;		// �ػ� �߽���ġ��, ī�޶� LookAt ��ġ ���� ����(diff) ��

	float			m_fTime;		// Ÿ���� ���󰡴� �ð�
	float			m_fSpeed;		// Ÿ���� ���󰡴� �ӵ� (�ʴ�)
	float			m_fAccTime;		// ���� �ð�

public:
	void SetLookAt(Vec2 _vLook) 
	{ 
		m_vLookAt = _vLook; 
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}
	void SetTarget(CObject* _pTarget) { m_pTargetObj = _pTarget; }

	Vec2 GetLookAt() { return m_vCurLookAt; }

	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }		// realPos -> renderPos (ī�޶� ����)
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }	// renderPos -> realPos (ī�޶� ������)

public:
	void Update();

private:
	void CallDiff();
};

