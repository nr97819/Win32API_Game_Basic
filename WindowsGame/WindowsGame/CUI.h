#pragma once
#include "CObject.h"


class CUI :
    public CObject
{
private:
    // UI가 자식 UI들을 다수 갖는다.
    vector<CUI*>            m_vecChildUI;

    // 부모 UI를 알수있어야 한다. (*쌍방 연결 필수)
    CUI*                    m_pParentUI;    // 부모 UI가 nullptr라면, 최상위 UI 객체이다.

    Vec2                    m_vFinalPos;    // 상대 값인 offset을 적용한 [최종 위치]

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }

    CUI* GetParent() { return m_pParentUI; }
    void AddChild(CUI* _pUI) 
    { 
        m_vecChildUI.push_back(_pUI); 
        _pUI->m_pParentUI = this; // 자식 UI 추가할 떄, 부모로서 [나]를 지정 (*계층 구조 중요)
    }

public:
    virtual void Update() override;
    virtual void FinalUpdate() override;
    virtual void Render(HDC _dc) override;

private:
    void update_child(); // 나 Update() 한 뒤, 호출될 자식 Update() 함수 - private
    void render_child(HDC _dc); // 나 Render() 한 뒤, 호출될 자식 Render() 함수 - private

    CLONE(CUI);
public:
    CUI();
    ~CUI();

};

