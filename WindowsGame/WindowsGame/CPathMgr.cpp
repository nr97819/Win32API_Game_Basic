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
	// ���� ��θ� ������ ����ش�.
	GetCurrentDirectory(255, m_szContentPath);

	// ���� ������ �̵�
	int iLen = wcslen(m_szContentPath);
	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");

	//SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);
}
