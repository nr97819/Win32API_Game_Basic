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

    // 카메라의 renderPos 영향을 받는 UI인지 bool 값
    bool                    m_bCamAffected;
    bool                    m_bMouseOn;
    // LBtn이 이 CUI 안에서 눌린 뒤, 아직 떼지 않은 상태인지 여부
    // (커서 위치와 관계없이, 이 CUI의 범위에서 눌린 뒤, 아직 LBtn이 Down 상태인 경우에 true)
    bool                    m_bLBtnDown;

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }
    CUI* GetParent() { return m_pParentUI; }
    
    // finalupdate에서 항상 계산해놓던 m_bMouseOn 값이 true인지 알려준다.
    bool IsMouseOn() { return m_bMouseOn; }

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
    void finalupdate_child();
    void render_child(HDC _dc); // 나 Render() 한 뒤, 호출될 자식 Render() 함수 - private

public:
    // UI 이벤트 관련 미리 계산해놓기 위한 함수들
    void MouseOnCheck();

public:
    // UI에서 발생하는 이벤트들
    // (CUI 파생해서 만들 class들에서도 이용될 기능들이므로, virtual로 정의)
    virtual void MouseOn();
    virtual void MouseLBtnDown();
    virtual void MosueLBtnUp();
    virtual void MosueLBtnClicked(); // LBtnDown과 LBtnUP을 혼합한 개념

    CLONE(CUI);
public:
    // 기본생성자 제거
    CUI(bool _bCamAff);
    virtual ~CUI();

    friend class CUIMgr;
};

