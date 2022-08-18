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

	// ��� [�ֻ��� �θ�] UI���� ��� vector
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI = (CUI*)vecUI[i];

		// pUI ��ü ���� ���콺 cursor�� �ö� ����
		if (pUI->IsMouseOn())
		{
			// mouse on �Լ� ȣ��
			pUI->MouseOn();

			if (KEY_TAP(KEY::LBTN))
			{
				pUI->MouseLBtnDown();
				// LBtn�� �� CUI �ȿ��� ���� ��, Down �����Ƿ� true�� ���� ����
				pUI->m_bLBtnDown = true;
			}
			else if (KEY_AWAY(KEY::LBTN))
			{
				pUI->MosueLBtnUp();

				// (*) Click �̺�Ʈ �߻�
				if (KEY_AWAY(KEY::LBTN))
				{
					pUI->MosueLBtnClicked();
				}
			}
		}
		// pUI ��ü ���� ���콺 cursor�� �ö��� ���� ����
		else
		{
			// (*) ��� ��������, LBTN�� �����ٸ� m_bLBtnDown�� false�� �����ؾ� �Ѵ�.
			if (KEY_AWAY(KEY::LBTN))
			{
				// LBtn�� �� CUI �ȿ��� ���� ��, Up �����Ƿ� false�� ���� ����
				pUI->m_bLBtnDown = false;
			}
		}
	}
}