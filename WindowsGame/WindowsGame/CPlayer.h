#pragma once
#include "CObject.h"


class CTexture;

class CPlayer :
    public CObject
{
private:
    // CTexture*       m_pTex; 
    // -> animation�� �̹� �ش� texture ������ �˰��ְ�
    // -> �̹� ��ϵǾ��ִ� animation�� Ű ���� ���� �ҷ��ͼ� �� ���̹Ƿ�

public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

private:
    void CreateMissile();

    // �� �ڽ��� Clone �ؼ� ��ȯ���ִ� �Լ�
    CLONE(CPlayer);

public:
    CPlayer();
    ~CPlayer();

    // Player�� ��������� ���� ���� ���ϴ� ���� �˰� �Ѿ�� (CObject*)
    // (�Ʒ� : �⺻ ����������� ����)
    /*CPlayer(const CPlayer& _origin)
        : CObject(_origin)
        , m_pTex(_origin.m_pTex)
    {}*/
};