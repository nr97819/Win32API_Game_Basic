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

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }

    CUI* GetParent() { return m_pParentUI; }
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
    void render_child(HDC _dc); // �� Render() �� ��, ȣ��� �ڽ� Render() �Լ� - private

    CLONE(CUI);
public:
    CUI();
    ~CUI();

};

