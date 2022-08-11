#pragma once


class CTexture;

class CResMgr
{
	SINGLE(CResMgr)
private:
	// map : 이진 탐색 트리 구조 + 자가 균형 (밸런스 자동 조정) 기능까지 있는 자료구조
	map<wstring, CTexture*> m_mapTex;


public:
	// 경로 _strRelativePath 에서, 키 _strKey 에 해당하는 ::리소스::를 Load 한다.
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* FindTexture(const wstring& _strKey); // 이미 존재하는 Key(리소스)인지 찾아보는 함수
};

