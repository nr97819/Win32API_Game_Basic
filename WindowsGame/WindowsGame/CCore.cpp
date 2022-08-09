#include "pch.h"
#include "CCore.h"

#include "CObject.h"


CObject g_obj;

CCore::CCore()
	: m_hWnd(nullptr)
	, m_ptResolution{}
	, m_hDC(nullptr)
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);
}

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정
	RECT rt = {0, 0, m_ptResolution.x, m_ptResolution.y};
	// 내가 원하는 해상도를 건네주면, 아래 함수에서 메뉴 등을 포함해서 조정한 값 반환해줌
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

	int width = rt.right - rt.left;
	int height = rt.bottom - rt.top;

	SetWindowPos(_hWnd, nullptr, 100, 100, width, height, 0);

	m_hDC = GetDC(m_hWnd);


	g_obj.m_ptPos = POINT{ m_ptResolution.x / 2, m_ptResolution.y / 2 };
	g_obj.m_ptScale = POINT{ 100, 100 };


	return S_OK;
}

void CCore::Progress()
{
	Update();
	Render();
}

void CCore::Update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		g_obj.m_ptPos.x += -1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_obj.m_ptPos.x += +1;
	}

}

void CCore::Render()
{
	// 그리기 (Render)
	Rectangle(m_hDC
		, g_obj.m_ptPos.x - g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2
		, g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2
		, g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2
	);
}
