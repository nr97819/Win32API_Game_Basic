#include "pch.h"
#include "CTexture.h"


CTexture::CTexture()
	: m_dc(0)
	, m_hBit(0)
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc); // 왜 여기서 해제하는거지?
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	// (*주의) 24비트 Bitmap 파일만 로드할 수 있다.
	// ... 수정 필요 ...

	// size에 0를 넘겨주면, default 사이즈를 가져와 준다 (resource 본연의 크기 모두)
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), 
		IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	// 제대로 Load하지 못한 경우, nullptr 예외 처리
	assert(m_hBit);
}
