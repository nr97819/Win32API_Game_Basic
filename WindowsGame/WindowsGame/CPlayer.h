#pragma once
#include "CObject.h"


class CTexture;

class CPlayer :
    public CObject
{
private:
    CTexture*       m_pTex;

public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

private:
    void CreateMissile();

public:
    CPlayer();
    ~CPlayer();
};

