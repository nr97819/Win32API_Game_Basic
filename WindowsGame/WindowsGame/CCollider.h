#pragma once


class CObject;

class CCollider
{
private:
	CObject* m_pOwner;

public:
	void finalupdate();

	friend class CObject;
};

