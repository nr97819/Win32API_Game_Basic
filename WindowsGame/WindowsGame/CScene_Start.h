#pragma once
#include "CScene.h"

class CScene_Start :
    public CScene
{
public:
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CScene_Start();
    ~CScene_Start();
};

