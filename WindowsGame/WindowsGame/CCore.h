#pragma once

class CCore
{
	SINGLE(CCore);
private:
	HWND		m_hWnd;
	POINT		m_ptResolution;
	HDC			m_hDC;

	HBITMAP		m_hBit;
	HDC			m_memDC;

	// 자주 사용하는 GDI Object
	HBRUSH		m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN		m_arrPen[(UINT)PEN_TYPE::END];

public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void Progress();

private:
	/*void Update();
	void Render();*/

private:
	void CreateBrushPen();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }

	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};

