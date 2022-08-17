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
	//HWND hMainWnd = CCore::GetInst()->GetMainHwnd(); // Main 윈도우인지 까지 확인하는 기능 (비활성화)
	HWND hFocusWnd = GetFocus();

	//if (hMainWnd == hFocusWnd)
	if (nullptr != hFocusWnd)
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			// 키가 눌려있다
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].ePrevPush)
				{
					// 이전에도 눌려있다
					m_vecKey[i].estate = KEY_STATE::HOLD;
				}
				else
				{
					// 이전에 눌려있지 않았다
					m_vecKey[i].estate = KEY_STATE::TAP;
				}

				m_vecKey[i].ePrevPush = true;
			}
			else
			{
				if (m_vecKey[i].ePrevPush)
				{
					// 이전에는 눌려있었다
					m_vecKey[i].estate = KEY_STATE::AWAY;
				}
				else
				{	// 이전에도 눌려있지 않았다
					m_vecKey[i].estate = KEY_STATE::NONE;
				}

				m_vecKey[i].ePrevPush = false;
			}
		}

		// Mouse 커서 위치 계산
		POINT ptPos = {};
		GetCursorPos(&ptPos);

		// GetCursorPos() 함수는 화면 전체 기준의 cursor 위치를 제공한다.
		// -> 우리의 wnd 창의 LeftTop을 빼줘야 쓸 수 있다.
		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos); // window에서 해당 함수도 제공한다.
		
		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y); // POINT를 Vec2로 변환
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
