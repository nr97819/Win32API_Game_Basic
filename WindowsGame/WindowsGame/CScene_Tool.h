#pragma once
#include "CScene.h"


class CScene_Tool :
    public CScene
{
private:


public:
    CScene_Tool();
    ~CScene_Tool();

public:
    virtual void Update() override;

    virtual void Enter() override;
    virtual void Exit() override;
};

