#include "pch.h"
#include "CPathMgr.h"

#include "CCore.h"


CPathMgr::CPathMgr()
	: m_szContentPath{}
{

}

CPathMgr::~CPathMgr()
{

}

void CPathMgr::Init()
{
	// 현재 경로를 변수에 담아준다.
	GetCurrentDirectory(255, m_szContentPath);

	// 상위 폴더로 이동
	int iLen = (int)wcslen(m_szContentPath);
	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin_release\\content\\");

	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);
}
