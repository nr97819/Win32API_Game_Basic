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

	// 더블 버퍼링 객체들 삭제
	DeleteDC(m_memDC); // CreateCompatibleDC로 생성한 경우, DeleteDC() 지우라고 MSDN에 써있음
	DeleteObject(m_hBit);

	// 미리 생성한 Pen 객체들 메모리 해제
	for (int i = 0; i < (int)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
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

	// 자주 사용하는 Brush / Pen 생성
	CreateBrushPen();

	// Manager 초기화
	CPathMgr::GetInst()->Init(); // 가장 먼저 초기화하는 것 주의 (Res 로드 시, 경로가 미리 잡혀야 한다.)
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
	CSceneMgr::GetInst()->Update(); // 모든 Scene과 그 아래 Object들 업데이트
	CCollisionMgr::GetInst()->Update(); // 업데이트 후 변동 된 정보에서, 새로운 충돌 있는지 검증


	/************************/
	/*		 Rendering		*/
	/************************/
	// 화면 Clear
	Rectangle(m_memDC
		, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// Scene 렌더링 (내부적으로 Object들도 모두 Render 타고 가는 구조)
	CSceneMgr::GetInst()->Render(m_memDC);

	// 최종 화면 출력
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY); // SRCCOPY : memory copy option

	// 창 상단에, 시간 정보 출력
	CTimeMgr::GetInst()->Render();


	/****************************/
	/*		 Event Excute		*/
	/****************************/
	// 모든 작업이 끝난 뒤, Event Manager 업데이트
	CEventMgr::GetInst()->Update(); // (이벤트 지연 처리)

}

void CCore::CreateBrushPen()
{
	// Hollow 브러시
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH); // delete 안해도 됨

	// Red / Green / Brush 펜
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}
