#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"
#include "CTexture.h"


CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
	// map�� ����ִ� ��� Texture ������ �޸� ����
	Safe_Delete_Map(m_mapTex);
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	// �̹� Load�ߴ� CTex���, �װ� �ٽ� �ְ� return
	CTexture* pTex = FindTexture(_strKey);
	if (pTex != nullptr)
	{
		return pTex;
	}

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// Texture�� Load
	pTex = new CTexture();
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey); // // �θ��� CRes�� �ش��ϴ� ����鵵 ä���־� �ش�.
	pTex->SetRelativePath(_strRelativePath);

	// ���� ������ Key�� CTex�� ��� map�� �������ش�. (���� Key�� ��ã�� & delete ��Ȱ�ϰ� �����ϵ���)
	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);
	
	// �ش� ���� ã�� ���� ��� (�������� �ʴ� ���)
	if (iter == m_mapTex.end())
	{
		return nullptr;
	}
	
	// ã�Ҵٸ�, �ش� Texture�� ��ȯ (second ���� : Texture)
	return iter->second;
}
