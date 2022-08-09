#include "pch.h"

#include "CCore.h"

CCore::CCore()
	: m_hWnd(nullptr)
	, m_ptResolution{}
{

}

CCore::~CCore()
{

}

int CCore::Init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;


	return S_OK;


}

void CCore::Progress()
{
	
}
