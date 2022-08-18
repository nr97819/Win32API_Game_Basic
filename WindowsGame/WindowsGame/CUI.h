#pragma once
#include "CObject.h"


class CUI :
    public CObject
{
private:
    // UI�� �ڽ� UI���� �ټ� ���´�.
    vector<CUI*>            m_vecChildUI;
    // �θ� UI�� �˼��־�� �Ѵ�. (*�ֹ� ���� �ʼ�)
    CUI*                    m_pParentUI;    // �θ� UI�� nullptr���, �ֻ��� UI ��ü�̴�.
    Vec2                    m_vFinalPos;    // ��� ���� offset�� ������ [���� ��ġ]

    // ī�޶��� renderPos ������ �޴� UI���� bool ��
    bool                    m_bCamAffected;
    bool                    m_bMouseOn;
    // LBtn�� �� CUI �ȿ��� ���� ��, ���� ���� ���� �������� ����
    // (Ŀ�� ��ġ�� �������, �� CUI�� �������� ���� ��, ���� LBtn�� Down ������ ��쿡 true)
    bool                    m_bLBtnDown;

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }
    CUI* GetParent() { return m_pParentUI; }
    
    // finalupdate���� �׻� ����س��� m_bMouseOn ���� true���� �˷��ش�.
    bool IsMouseOn() { return m_bMouseOn; }

    void AddChild(CUI* _pUI) 
    { 
        m_vecChildUI.push_back(_pUI); 
        _pUI->m_pParentUI = this; // �ڽ� UI �߰��� ��, �θ�μ� [��]�� ���� (*���� ���� �߿�)
    }

public:
    virtual void Update() override;
    virtual void FinalUpdate() override;
    virtual void Render(HDC _dc) override;

private:
    void update_child(); // �� Update() �� ��, ȣ��� �ڽ� Update() �Լ� - private
    void finalupdate_child();
    void render_child(HDC _dc); // �� Render() �� ��, ȣ��� �ڽ� Render() �Լ� - private

public:
    // UI �̺�Ʈ ���� �̸� ����س��� ���� �Լ���
    void MouseOnCheck();

public:
    // UI���� �߻��ϴ� �̺�Ʈ��
    // (CUI �Ļ��ؼ� ���� class�鿡���� �̿�� ��ɵ��̹Ƿ�, virtual�� ����)
    virtual void MouseOn();
    virtual void MouseLBtnDown();
    virtual void MosueLBtnUp();
    virtual void MosueLBtnClicked(); // LBtnDown�� LBtnUP�� ȥ���� ����

    CLONE(CUI);
public:
    // �⺻������ ����
    CUI(bool _bCamAff);
    virtual ~CUI();

    friend class CUIMgr;
};

