#pragma once


class CPathMgr
{
	SINGLE(CPathMgr);
private:
	wchar_t			m_szContentPath[255]; // Windows의 경로는 최대 255자 제한이 되어있으므로,

public:
	void Init();
	const wchar_t* GetContentPath() { return m_szContentPath; }
};

