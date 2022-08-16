#pragma once
#include "CObject.h"


class CTexture;

class CPlayer :
    public CObject
{
private:
    // CTexture*       m_pTex; 
    // -> animation이 이미 해당 texture 정보를 알고있고
    // -> 이미 등록되어있는 animation을 키 값을 통해 불러와서 쓸 것이므로

public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

private:
    void CreateMissile();

    // 나 자신을 Clone 해서 반환해주는 함수
    CLONE(CPlayer);

public:
    CPlayer();
    ~CPlayer();

    // Player는 복사생성자 별도 구현 안하는 이유 알고 넘어가기 (CObject*)
    // (아래 : 기본 복사생성자의 형태)
    /*CPlayer(const CPlayer& _origin)
        : CObject(_origin)
        , m_pTex(_origin.m_pTex)
    {}*/
};