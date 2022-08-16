#pragma once


class CAnimator;
class CTexture;

struct tAnimFrm
{
	Vec2 vLT;			// �ڸ� LeftTop ��ġ
	Vec2 vSlice;		// �ڸ� ũ��
	float fDuration;	// ���� �ð�
};

class CAnimation
{
private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;		// animatino�� ����ϴ� ���ҽ��� ���� ����
	vector<tAnimFrm>	m_vecFrm;	// �� �����ӿ� ���� ���� tAnimFrm�� ���� ����
	int					m_iCurFrm;	// ���� frame (�׷��� ���� frame)
	float				m_fAccTime; // ���� �ð�

	bool				m_bFinish;	// 1���� ��� �Ϸ� ����

public:
	void Update();
	void Render(HDC _dc);

public:
	const wstring& GetName() { return m_strName; }
	
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx) 
	{ 
		m_bFinish = false;		// finish ���� ����
		m_iCurFrm = _iFrameIdx;	// �ش� index�� ������ ����
		m_fAccTime = 0.f;		// ���� �ð� 0.f�� �ʱ�ȭ
		// -> ���� �ִ� �� ����. (���߿� ���� ����)
	}

private:
	// �� �� ������ �̸��� �ٽô� �ٲ�� �ȵǹǷ�, private���� ����
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	void Create(const wstring& _strName, CTexture* _pTex
		, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

