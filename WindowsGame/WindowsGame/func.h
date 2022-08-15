#pragma once


class CObject;

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup);
void DeleteObject(CObject* _pObj);
void ChangeScene(SCENE_TYPE _eNext);


// 어떤 vector 형태에 대해 Delete를 수행할 지, 알 수 없으므로 template을 이용
template<typename T> // (*) Template은 header 파일에 모두 구현해야 한다. (주의)
void Safe_Delete_Vec(vector<T>& _vec) // 원본 vec를 받아서 비워야하므로, 참조(&) 형태로 받는 것 주의
{
	// (32개 그룹 중), 특정 그룹 (eType)의 오브젝트의 memory 해제 & 그룹 vector clear()
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if(nullptr != _vec[i])
			delete _vec[i];
	}

	_vec.clear();
}

// vector와 같지만, Type이 2개가 들어오는 것 주의
template<typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	// template 내에서 inner 클래스를 이용하려면 (ex. map::iteraotr)
	// -> typename을 반드시 적어줘야 한다. (2015년 쯤부터 변경됐다.)
	typename map<T1, T2>::iterator iter = _map.begin();

	for (; iter != _map.end(); ++iter)
	{
		if (nullptr != iter->second)
		{
			delete iter->second; // 사실상 second 원소만 안전하게 delete 완료됐으면 막 지워도 되므로,
		}
	}

	_map.clear();
}