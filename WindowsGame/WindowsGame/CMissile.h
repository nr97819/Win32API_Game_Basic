#pragma once
#include "CObject.h"

class CMissile :
    public CObject
{
private:
    float         m_fTheta; // (이동 방향 = 각도)

    Vec2          m_vDir;   // 나아갈 뱡향(물리 벡터)


public:
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir) 
    { 
        m_vDir = _vDir;
        m_vDir.Normalize();
    }

public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

public:
    virtual void OnCollisionEnter(CCollider* pOther) override;

    // 나 자신을 Clone 해서 반환해주는 함수
    CLONE(CMissile);

public:
    CMissile();
    ~CMissile();

};

