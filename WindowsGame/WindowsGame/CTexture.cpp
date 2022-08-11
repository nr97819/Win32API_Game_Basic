#include "pch.h"
#include "CTexture.h"


CTexture::CTexture()
	: m_dc(0)
	, m_hBit(0)
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc); // �� ���⼭ �����ϴ°���?
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	// (*����) 24��Ʈ Bitmap ���ϸ� �ε��� �� �ִ�.
	// ... ���� �ʿ� ...

	// size�� 0�� �Ѱ��ָ�, default ����� ������ �ش� (resource ������ ũ�� ���)
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), 
		IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	// ����� Load���� ���� ���, nullptr ���� ó��
	assert(m_hBit);
}
