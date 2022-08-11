#include "pch.h"
#include "CTexture.h"

#include "CCore.h"


CTexture::CTexture()
	: m_dc(0)
	, m_hBit(0)
	, m_bitInfo{}
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

	// Bitmap�� ����� DC
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	// Bitamp�� DC ����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);
	
	// width, height�� �޾ƿ��� ��� (����ü�� ��� �´�)
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}
