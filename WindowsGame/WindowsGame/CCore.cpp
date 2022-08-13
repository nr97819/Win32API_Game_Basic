#include "pch.h"
#include "CCore.h"

#include "CObject.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"

CCore::CCore()
	: m_hWnd(0)
	, m_ptResolution{}
	, m_hDC(0)
	, m_hBit(0)
	, m_memDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC);

	// ���� ���۸� ��ü�� ����
	DeleteDC(m_memDC); // CreateCompatibleDC�� ������ ���, DeleteDC() ������ MSDN�� ������
	DeleteObject(m_hBit);

	// �̸� ������ Pen ��ü�� �޸� ����
	for (int i = 0; i < (int)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
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

	// ���� ����ϴ� Brush / Pen ����
	CreateBrushPen();

	// Manager �ʱ�ȭ
	CPathMgr::GetInst()->Init(); // ���� ���� �ʱ�ȭ�ϴ� �� ���� (Res �ε� ��, ��ΰ� �̸� ������ �Ѵ�.)
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


	/****************************/
	/*		 Object Update		*/
	/****************************/
	CSceneMgr::GetInst()->Update(); // ��� Scene�� �� �Ʒ� Object�� ������Ʈ
	CCollisionMgr::GetInst()->Update(); // ������Ʈ �� ���� �� ��������, ���ο� �浹 �ִ��� ����


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

	// â ��ܿ�, �ð� ���� ���
	CTimeMgr::GetInst()->Render();


	/****************************/
	/*		 Event Excute		*/
	/****************************/
	// ��� �۾��� ���� ��, Event Manager ������Ʈ
	CEventMgr::GetInst()->Update(); // (�̺�Ʈ ���� ó��)

}

void CCore::CreateBrushPen()
{
	// Hollow �귯��
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH); // delete ���ص� ��

	// Red / Green / Brush ��
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}
