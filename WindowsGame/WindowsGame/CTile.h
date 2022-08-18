#pragma once
#include "CObject.h"


class CTexture;

class CTile :
    public CObject
{
private:
    CTexture*       m_pTileTex;
    int             m_iImgIdx; // -1�� ���, �ƹ��͵� �������� ����

public:
    void SetTexture(CTexture* _pTex) { m_pTileTex = _pTex; }
    
    void IncreaseImgIdx() { ++m_iImgIdx; }

public:
    virtual void Update();
    virtual void Render(HDC _dc);

    CLONE(CTile);
public:
    CTile();
    ~CTile();

};

