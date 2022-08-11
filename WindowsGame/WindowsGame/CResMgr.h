#pragma once


class CTexture;

class CResMgr
{
	SINGLE(CResMgr)
private:
	// map : ���� Ž�� Ʈ�� ���� + �ڰ� ���� (�뷱�� �ڵ� ����) ��ɱ��� �ִ� �ڷᱸ��
	map<wstring, CTexture*> m_mapTex;


public:
	// ��� _strRelativePath ����, Ű _strKey �� �ش��ϴ� ::���ҽ�::�� Load �Ѵ�.
	CTexture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);
	CTexture* FindTexture(const wstring& _strKey); // �̹� �����ϴ� Key(���ҽ�)���� ã�ƺ��� �Լ�
};

