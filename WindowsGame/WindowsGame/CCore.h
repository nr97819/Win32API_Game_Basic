#pragma once

class CCore
{
	SINGLE(CCore);
private:
	HWND		m_hWnd;
	POINT		m_ptResolution;

public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void Progress();
};

