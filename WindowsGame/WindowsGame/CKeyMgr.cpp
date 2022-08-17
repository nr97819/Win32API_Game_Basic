#include "pch.h"
#include "CKeyMgr.h"

#include "CCore.h"

int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	'Q', 'W', 'E', 'R', 'T',
	'Y', 'U', 'I', 'O', 'P',
	'A', 'S', 'D', 'F', 'G',
	'Z', 'X', 'C', 'V', 'B',

	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE,

	VK_LBUTTON,
	VK_RBUTTON
};

CKeyMgr::CKeyMgr()
	: m_vecKey{}
	, m_vCurMousePos{}
{
}

CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });
	}
}

void CKeyMgr::Update()
{
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd(); // Main ���������� ���� Ȯ���ϴ� ��� (��Ȱ��ȭ)
	HWND hFocusWnd = GetFocus();

	//if (hMainWnd == hFocusWnd)
	if (nullptr != hFocusWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			// Ű�� �����ִ�
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].ePrevPush)
				{
					// �������� �����ִ�
					m_vecKey[i].estate = KEY_STATE::HOLD;
				}
				else
				{
					// ������ �������� �ʾҴ�
					m_vecKey[i].estate = KEY_STATE::TAP;
				}

				m_vecKey[i].ePrevPush = true;
			}
			else
			{
				if (m_vecKey[i].ePrevPush)
				{
					// �������� �����־���
					m_vecKey[i].estate = KEY_STATE::AWAY;
				}
				else
				{	// �������� �������� �ʾҴ�
					m_vecKey[i].estate = KEY_STATE::NONE;
				}

				m_vecKey[i].ePrevPush = false;
			}
		}

		// Mouse Ŀ�� ��ġ ���
		POINT ptPos = {};
		GetCursorPos(&ptPos);

		// GetCursorPos() �Լ��� ȭ�� ��ü ������ cursor ��ġ�� �����Ѵ�.
		// -> �츮�� wnd â�� LeftTop�� ����� �� �� �ִ�.
		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos); // window���� �ش� �Լ��� �����Ѵ�.
		
		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y); // POINT�� Vec2�� ��ȯ
	}
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].ePrevPush = false;

			if (KEY_STATE::TAP == m_vecKey[i].estate)
			{
				m_vecKey[i].estate = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::HOLD == m_vecKey[i].estate)
			{
				m_vecKey[i].estate = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].estate)
			{
				m_vecKey[i].estate = KEY_STATE::NONE;
			}
		}
	}
}
