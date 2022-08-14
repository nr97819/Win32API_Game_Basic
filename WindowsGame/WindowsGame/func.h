#pragma once


class CObject;

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup);
void DeleteObject(CObject* _pObj);
void ChangeScene(SCENE_TYPE _eNext);


// � vector ���¿� ���� Delete�� ������ ��, �� �� �����Ƿ� template�� �̿�
template<typename T> // (*) Template�� header ���Ͽ� ��� �����ؾ� �Ѵ�. (����)
void Safe_Delete_Vec(vector<T>& _vec) // ���� vec�� �޾Ƽ� ������ϹǷ�, ����(&) ���·� �޴� �� ����
{
	// (32�� �׷� ��), Ư�� �׷� (eType)�� ������Ʈ�� memory ���� & �׷� vector clear()
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if(nullptr != _vec[i])
			delete _vec[i];
	}

	_vec.clear();
}

