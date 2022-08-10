#include "pch.h"
#include "CCore.h"

#include "CObject.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
{}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	// ���� ���۸� ��ü�� ����
	DeleteDC(m_memDC); // CreateCompatibleDC�� ������ ���, DeleteDC() ������ MSDN�� ������
	DeleteObject(m_hBit);
}

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;

	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = {0, 0, m_ptResolution.x, m_ptResolution.y};
	// ���� ���ϴ� �ػ󵵸� �ǳ��ָ�, �Ʒ� �Լ����� �޴� ���� �����ؼ� ������ �� ��ȯ����
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

	int width = rt.right - rt.left;
	int height = rt.bottom - rt.top;

	SetWindowPos(_hWnd, nullptr, 100, 100, width, height, 0);

	m_hDC = GetDC(m_hWnd);

	// ���� ���۸� �뵵�� Bitmap�� DC�� �����.
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	// Manager �ʱ�ȭ
	CTimeMgr::GetInst()->Init();
	CKeyMgr::GetInst()->Init();
	CSceneMgr::GetInst()->Init();

	return S_OK;
}

void CCore::Progress()
{
	// Manager Update
	CTimeMgr::GetInst()->Update();
	CKeyMgr::GetInst()->Update();

	CSceneMgr::GetInst()->Update();


	/************************/
	/*		 Rendering		*/
	/************************/

	// ȭ�� Clear
	Rectangle(m_memDC
		, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// Scene ������ (���������� Object�鵵 ��� Render Ÿ�� ���� ����)
	CSceneMgr::GetInst()->Render(m_memDC);

	// ���� ȭ�� ���
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY); // SRCCOPY : memory copy option
}
