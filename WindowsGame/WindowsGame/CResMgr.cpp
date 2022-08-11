#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"


CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
	// map에 들어있는 모든 Texture 포인터 메모리 해제
	map<wstring, CTexture*>::iterator iter = m_mapTex.begin();
	for (; iter != m_mapTex.end(); ++iter)
	{
		delete iter->second;
		iter->second = nullptr;
	}
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 이미 Load했던 CTex라면, 그걸 다시 주고 return
	CTexture* pTex = FindTexture(_strKey);
	if (pTex != nullptr)
	{
		return pTex;
	}

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// Texture를 Load
	pTex = new CTexture();
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey); // // 부모인 CRes에 해당하는 내용들도 채워넣어 준다.
	pTex->SetRelativePath(_strRelativePath);

	// 새로 생성한 Key와 CTex를 멤버 map에 저장해준다. (추후 Key로 되찾기 & delete 원활하게 가능하도록)
	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);
	
	// 해당 값을 찾지 못한 경우 (존재하지 않는 경우)
	if (iter == m_mapTex.end())
	{
		return nullptr;
	}
	
	// 찾았다면, 해당 Texture를 반환 (second 원소 : Texture)
	return iter->second;
}
