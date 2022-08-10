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

public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void Progress();

private:
	void Update();
	void Render();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	POINT GetResolution() { return m_ptResolution; }
};

