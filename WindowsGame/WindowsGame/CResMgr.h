#pragma once


class CTexture;
class CRes;

class CResMgr
{
	SINGLE(CResMgr)
private:
	// map : 이진 탐색 트리 구조 + 자가 균형 (밸런스 자동 조정) 기능까지 있는 자료구조
	map<wstring, CRes*> m_mapTex; // (CTexture*)가 아닌, (CRes*)로 저장하도록 수정


public:
	// 경로 _strRelativePath 에서, 키 _strKey 에 해당하는 ::리소스::를 Load 한다.
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* FindTexture(const wstring& _strKey); // 이미 존재하는 Key(리소스)인지 찾아보는 함수
};

