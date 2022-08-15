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

// vector�� ������, Type�� 2���� ������ �� ����
template<typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	// template ������ inner Ŭ������ �̿��Ϸ��� (ex. map::iteraotr)
	// -> typename�� �ݵ�� ������� �Ѵ�. (2015�� ����� ����ƴ�.)
	typename map<T1, T2>::iterator iter = _map.begin();

	for (; iter != _map.end(); ++iter)
	{
		if (nullptr != iter->second)
		{
			delete iter->second; // ��ǻ� second ���Ҹ� �����ϰ� delete �Ϸ������ �� ������ �ǹǷ�,
		}
	}

	_map.clear();
}