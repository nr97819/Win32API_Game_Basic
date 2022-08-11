#pragma once
#include "CObject.h"

class CPlayer :
    public CObject
{
private:

public:
    virtual void Update() override;
    //virtual void Render(HDC _dc) override;

private:
    void CreateMissile();

public:
    CPlayer();
    ~CPlayer();
};

