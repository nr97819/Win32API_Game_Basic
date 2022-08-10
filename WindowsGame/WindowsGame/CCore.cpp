#include "pch.h"
#include "CCore.h"

#include "CObject.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

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

	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = {0, 0, m_ptResolution.x, m_ptResolution.y};
	// ���� ���ϴ� �ػ󵵸� �ǳ��ָ�, �Ʒ� �Լ����� �޴� ���� �����ؼ� ������ �� ��ȯ����
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);

	int width = rt.right - rt.left;
	int height = rt.bottom - rt.top;

	SetWindowPos(_hWnd, nullptr, 100, 100, width, height, 0);

	m_hDC = GetDC(m_hWnd);

	// Manager �ʱ�ȭ
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
	// �׸���
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_hDC
		, int(vPos.x - vScale.x / 2.f)
		, int(vPos.y - vScale.y / 2.f)
		, int(vPos.x + vScale.x / 2.f)
		, int(vPos.y + vScale.y / 2.f)
	);
}
