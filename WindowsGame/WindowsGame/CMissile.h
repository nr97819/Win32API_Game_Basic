#pragma once
#include "CObject.h"

class CMissile :
    public CObject
{
private:
    float         m_fDir;

public:
    void SetDir(bool _bUp)
    {
        if (_bUp)
            m_fDir = -1.f;
        else
            m_fDir = 1.f;
    }

public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

public:
    CMissile();
    ~CMissile();
};

