#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CKeyMgr.h"

#include "CScene.h"
#include "CUI.h"


CUIMgr::CUIMgr()
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::Update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// 모든 [최상위 부모] UI들이 담긴 vector
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI = (CUI*)vecUI[i];

		// pUI 객체 위에 마우스 cursor가 올라간 상태
		if (pUI->IsMouseOn())
		{
			// mouse on 함수 호출
			pUI->MouseOn();

			if (KEY_TAP(KEY::LBTN))
			{
				pUI->MouseLBtnDown();
				// LBtn이 이 CUI 안에서 눌린 뒤, Down 됐으므로 true로 상태 변경
				pUI->m_bLBtnDown = true;
			}
			else if (KEY_AWAY(KEY::LBTN))
			{
				pUI->MosueLBtnUp();

				// (*) Click 이벤트 발생
				if (KEY_AWAY(KEY::LBTN))
				{
					pUI->MosueLBtnClicked();
				}
			}
		}
		// pUI 객체 위에 마우스 cursor가 올라가지 않은 상태
		else
		{
			// (*) 어느 시점에라도, LBTN이 떼졌다면 m_bLBtnDown를 false로 변경해야 한다.
			if (KEY_AWAY(KEY::LBTN))
			{
				// LBtn이 이 CUI 안에서 눌린 뒤, Up 됐으므로 false로 상태 변경
				pUI->m_bLBtnDown = false;
			}
		}
	}
}