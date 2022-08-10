#include "pch.h"
#include "CCore.h"

#include "CObject.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

CObject g_obj;

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	// 더블 버퍼링 객체들 삭제
	DeleteDC(m_memDC); // CreateCompatibleDC로 생성한 경우, DeleteDC() 지우라고 MSDN에 써있음
	DeleteObject(m_hBit);
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

	// 이중 버퍼링 용도의 Bitmap과 DC를 만든다.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	// Manager 초기화
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();

	g_obj.SetPos(Vec2{ m_ptResolution.x / 2.f, m_ptResolution.y / 2.f });
	g_obj.SetScale(Vec2{ 100.f, 100.f });

	return S_OK;
}

void CCore::Progress()
{
	Update();

	Render();
}

void CCore::Update()
{
	// Manager Update
	CTimeMgr::GetInst()->Update();

	Vec2 vPos = g_obj.GetPos();

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vPos.x -= 100.f * fDT;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 100.f * fDT;
	}

	g_obj.SetPos(vPos);
}

void CCore::Render()
{
	// 화면 Clear
	Rectangle(m_memDC
		, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// 그리기
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_memDC
		, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f)
	);

	// 최종 화면 출력
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, 
		m_memDC, 0, 0, SRCCOPY); // SRCCOPY : memory copy option
}
