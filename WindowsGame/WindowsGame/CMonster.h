#pragma once
#include "CObject.h"

class CMonster :
    public CObject
{
private:
    Vec2            m_vCenterPos;
    float           m_fSpeed;
    float           m_fMaxDistance;
    int             m_iDir; // ������� (1: ����, -1: ����)

    int             m_iHP;

public:
    CMonster();
    ~CMonster();

public:
    virtual void Update() override;

public:
    float GetSpeed() { return m_fSpeed; }
    void SetSpeed(float _f) { m_fSpeed = _f; }
    void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }

public:
    virtual void OnCollisionEnter(CCollider* _pOther) override;

};

